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
struct twl4030_bci {scalar_t__ ac_mode; } ;

/* Variables and functions */
 scalar_t__ CHARGE_OFF ; 
 int /*<<< orphan*/  TWL4030_BCIAUTOAC ; 
 int twl4030_clear_set_boot_bci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_charger_enable_ac(struct twl4030_bci *bci, bool enable)
{
	int ret;

	if (bci->ac_mode == CHARGE_OFF)
		enable = false;

	if (enable)
		ret = twl4030_clear_set_boot_bci(0, TWL4030_BCIAUTOAC);
	else
		ret = twl4030_clear_set_boot_bci(TWL4030_BCIAUTOAC, 0);

	return ret;
}