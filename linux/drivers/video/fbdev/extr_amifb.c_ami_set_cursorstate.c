#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_cursorstate {int /*<<< orphan*/  mode; int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct TYPE_2__ {int /*<<< orphan*/  crsr_y; int /*<<< orphan*/  crsr_x; } ;
struct amifb_par {TYPE_1__ crsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_CURSOR_OFF ; 
 int /*<<< orphan*/  cursormode ; 
 int cursorstate ; 
 int do_cursor ; 

__attribute__((used)) static int ami_set_cursorstate(struct fb_cursorstate *state,
			       struct amifb_par *par)
{
	par->crsr.crsr_x = state->xoffset;
	par->crsr.crsr_y = state->yoffset;
	if ((cursormode = state->mode) == FB_CURSOR_OFF)
		cursorstate = -1;
	do_cursor = 1;
	return 0;
}