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
struct pm2xxx_charger {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* desc; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PM2XXX_BATT_WD_KICK ; 
 scalar_t__ POWER_SUPPLY_TYPE_MAINS ; 
 int /*<<< orphan*/  WD_TIMER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int pm2xxx_reg_write (struct pm2xxx_charger*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pm2xxx_charger* to_pm2xxx_charger_ac_device_info (struct ux500_charger*) ; 

__attribute__((used)) static int pm2xxx_charger_watchdog_kick(struct ux500_charger *charger)
{
	int ret;
	struct pm2xxx_charger *pm2;

	if (charger->psy->desc->type == POWER_SUPPLY_TYPE_MAINS)
		pm2 = to_pm2xxx_charger_ac_device_info(charger);
	else
		return -ENXIO;

	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_WD_KICK, WD_TIMER);
	if (ret)
		dev_err(pm2->dev, "Failed to kick WD!\n");

	return ret;
}