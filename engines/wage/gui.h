/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * MIT License:
 *
 * Copyright (c) 2009 Alexei Svitkine, Eugene Sandulenko
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef WAGE_GUI_H
#define WAGE_GUI_H

#include "common/str-array.h"
#include "graphics/font.h"
#include "graphics/managed_surface.h"
#include "common/events.h"
#include "common/rect.h"

#include "wage/macwindow.h"
#include "wage/macwindowmanager.h"

namespace Wage {

class Menu;
class Scene;
class WageEngine;

enum {
	kCursorHeight = 12
};

class Gui {
public:
	Gui(WageEngine *engine);
	~Gui();

	void draw();
	void appendText(const char *str);
	void clearOutput();
	bool processEvent(Common::Event &event);

	void drawInput();
	void setSceneDirty() { _sceneDirty = true; }
	void regenCommandsMenu();
	void regenWeaponsMenu();

	void actionCopy();
	void actionPaste();
	void actionUndo();
	void actionClear();
	void actionCut();
	void disableUndo();
	void disableAllMenus();
	void enableNewGameMenus();

	bool processSceneEvents(WindowClick click, Common::Event &event);
	bool processConsoleEvents(WindowClick click, Common::Event &event);
	void executeMenuCommand(int action, Common::String &text);

private:
	void drawScene();
	void drawConsole();
	void undrawCursor();
	void renderConsole(Graphics::ManagedSurface *g, const Common::Rect &r);
	void flowText(Common::String &str);
	const Graphics::Font *getConsoleFont();
	const Graphics::Font *getTitleFont();
	void startMarking(int x, int y);
	int calcTextX(int x, int textLine);
	int calcTextY(int y);
	void updateTextSelection(int x, int y);

public:
	Graphics::ManagedSurface _screen;
	int _cursorX, _cursorY;
	bool _cursorState;

	WageEngine *_engine;

	bool _cursorDirty;
	Common::Rect _cursorRect;
	bool _cursorOff;

	Scene *_scene;

	MacWindowManager _wm;
	MacWindow *_sceneWindow;
	MacWindow *_consoleWindow;

private:
	Graphics::ManagedSurface _console;
	Menu *_menu;
	bool _sceneDirty;
	bool _consoleDirty;

	Common::StringArray _out;
	Common::StringArray _lines;
	uint _scrollPos;
	int _consoleLineHeight;
	uint _consoleNumLines;
	bool _consoleFullRedraw;

	bool _inTextSelection;
	int _selectionStartX;
	int _selectionStartY;
	int _selectionEndX;
	int _selectionEndY;

	Common::String _clipboard;
	Common::String _undobuffer;

	int _inputTextLineNum;

	int _commandsMenuId;
	int _weaponsMenuId;
};

} // End of namespace Wage

#endif
