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
struct brcms_hardware {int maccontrol; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_mctrl_write (struct brcms_hardware*) ; 

void brcms_b_mctrl(struct brcms_hardware *wlc_hw, u32 mask, u32 val)
{
	u32 maccontrol;
	u32 new_maccontrol;

	if (val & ~mask)
		return; /* error condition */
	maccontrol = wlc_hw->maccontrol;
	new_maccontrol = (maccontrol & ~mask) | val;

	/* if the new maccontrol value is the same as the old, nothing to do */
	if (new_maccontrol == maccontrol)
		return;

	/* something changed, cache the new value */
	wlc_hw->maccontrol = new_maccontrol;

	/* write the new values with overrides applied */
	brcms_c_mctrl_write(wlc_hw);
}