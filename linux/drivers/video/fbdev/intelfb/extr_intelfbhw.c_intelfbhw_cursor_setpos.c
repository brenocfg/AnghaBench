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
typedef  int u32 ;
struct TYPE_2__ {int physical; } ;
struct intelfb_info {TYPE_1__ cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_A_BASEADDR ; 
 int /*<<< orphan*/  CURSOR_A_POSITION ; 
 int CURSOR_POS_MASK ; 
 int CURSOR_X_SHIFT ; 
 int CURSOR_Y_SHIFT ; 
 int /*<<< orphan*/  DBG_MSG (char*,int,int) ; 
 scalar_t__ IS_I9XX (struct intelfb_info*) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 

void intelfbhw_cursor_setpos(struct intelfb_info *dinfo, int x, int y)
{
	u32 tmp;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_setpos: (%d, %d)\n", x, y);
#endif

	/*
	 * Sets the position. The coordinates are assumed to already
	 * have any offset adjusted. Assume that the cursor is never
	 * completely off-screen, and that x, y are always >= 0.
	 */

	tmp = ((x & CURSOR_POS_MASK) << CURSOR_X_SHIFT) |
	      ((y & CURSOR_POS_MASK) << CURSOR_Y_SHIFT);
	OUTREG(CURSOR_A_POSITION, tmp);

	if (IS_I9XX(dinfo))
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
}