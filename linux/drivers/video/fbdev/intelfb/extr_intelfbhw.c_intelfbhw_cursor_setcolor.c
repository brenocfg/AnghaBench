#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct intelfb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_A_PALETTE0 ; 
 int /*<<< orphan*/  CURSOR_A_PALETTE1 ; 
 int /*<<< orphan*/  CURSOR_A_PALETTE2 ; 
 int /*<<< orphan*/  CURSOR_A_PALETTE3 ; 
 int CURSOR_PALETTE_MASK ; 
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int) ; 

void intelfbhw_cursor_setcolor(struct intelfb_info *dinfo, u32 bg, u32 fg)
{
#if VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_setcolor\n");
#endif

	OUTREG(CURSOR_A_PALETTE0, bg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE1, fg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE2, fg & CURSOR_PALETTE_MASK);
	OUTREG(CURSOR_A_PALETTE3, bg & CURSOR_PALETTE_MASK);
}