#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ux500_charger {TYPE_2__* psy; } ;
struct ab8500_charger {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_CHARGER ; 
 int /*<<< orphan*/  AB8500_CHARG_WD_CTRL ; 
 int /*<<< orphan*/  CHARG_WD_KICK ; 
 int ENXIO ; 
 scalar_t__ POWER_SUPPLY_TYPE_MAINS ; 
 scalar_t__ POWER_SUPPLY_TYPE_USB ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct ab8500_charger* to_ab8500_charger_ac_device_info (struct ux500_charger*) ; 
 struct ab8500_charger* to_ab8500_charger_usb_device_info (struct ux500_charger*) ; 

__attribute__((used)) static int ab8500_charger_watchdog_kick(struct ux500_charger *charger)
{
	int ret;
	struct ab8500_charger *di;

	if (charger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		di = to_ab8500_charger_ac_device_info(charger);
	else if (charger->psy->desc->type == POWER_SUPPLY_TYPE_USB)
		di = to_ab8500_charger_usb_device_info(charger);
	else
		return -ENXIO;

	ret = abx500_set_register_interruptible(di->dev, AB8500_CHARGER,
		AB8500_CHARG_WD_CTRL, CHARG_WD_KICK);
	if (ret)
		dev_err(di->dev, "Failed to kick WD!\n");

	return ret;
}