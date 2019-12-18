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

/* Variables and functions */
 int /*<<< orphan*/  PWR_DEVOFF ; 
 int STARTON_CHG ; 
 int STARTON_VBUS ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_P1_SW_EVENTS ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int twl4030_starton_mask_and_set (int,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void twl4030_power_off(void)
{
	int err;

	/* Disable start on charger or VBUS as it can break poweroff */
	err = twl4030_starton_mask_and_set(STARTON_VBUS | STARTON_CHG, 0);
	if (err)
		pr_err("TWL4030 Unable to configure start-up\n");

	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, PWR_DEVOFF,
			       TWL4030_PM_MASTER_P1_SW_EVENTS);
	if (err)
		pr_err("TWL4030 Unable to power off\n");
}