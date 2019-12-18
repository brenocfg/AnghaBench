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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  as3722; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS3722_POWER_OFF ; 
 int /*<<< orphan*/  AS3722_RESET_CONTROL_REG ; 
 TYPE_1__* as3722_pm_poweroff ; 
 int as3722_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void as3722_pm_power_off(void)
{
	int ret;

	if (!as3722_pm_poweroff) {
		pr_err("AS3722 poweroff is not initialised\n");
		return;
	}

	ret = as3722_update_bits(as3722_pm_poweroff->as3722,
		AS3722_RESET_CONTROL_REG, AS3722_POWER_OFF, AS3722_POWER_OFF);
	if (ret < 0)
		dev_err(as3722_pm_poweroff->dev,
			"RESET_CONTROL_REG update failed, %d\n", ret);
}