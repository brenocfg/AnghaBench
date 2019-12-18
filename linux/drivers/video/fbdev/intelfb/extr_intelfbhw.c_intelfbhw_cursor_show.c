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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  physical; } ;
struct intelfb_info {int cursor_on; TYPE_1__ cursor; scalar_t__ mobile; scalar_t__ cursor_blanked; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_A_BASEADDR ; 
 int /*<<< orphan*/  CURSOR_A_CONTROL ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int /*<<< orphan*/  CURSOR_ENABLE ; 
 int /*<<< orphan*/  CURSOR_MODE_64_4C_AX ; 
 int /*<<< orphan*/  CURSOR_MODE_MASK ; 
 int /*<<< orphan*/  DBG_MSG (char*) ; 
 int /*<<< orphan*/  INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_I9XX (struct intelfb_info*) ; 
 int /*<<< orphan*/  OUTREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intelfbhw_cursor_show(struct intelfb_info *dinfo)
{
	u32 tmp;

#if VERBOSE > 0
	DBG_MSG("intelfbhw_cursor_show\n");
#endif

	dinfo->cursor_on = 1;

	if (dinfo->cursor_blanked)
		return;

	if (dinfo->mobile || IS_I9XX(dinfo)) {
		if (!dinfo->cursor.physical)
			return;
		tmp = INREG(CURSOR_A_CONTROL);
		tmp &= ~CURSOR_MODE_MASK;
		tmp |= CURSOR_MODE_64_4C_AX;
		OUTREG(CURSOR_A_CONTROL, tmp);
		/* Flush changes */
		OUTREG(CURSOR_A_BASEADDR, dinfo->cursor.physical);
	} else {
		tmp = INREG(CURSOR_CONTROL);
		tmp |= CURSOR_ENABLE;
		OUTREG(CURSOR_CONTROL, tmp);
	}
}