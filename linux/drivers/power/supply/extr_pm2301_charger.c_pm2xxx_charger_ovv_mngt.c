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
struct TYPE_4__ {int /*<<< orphan*/  psy; } ;
struct TYPE_3__ {int ovv; } ;
struct pm2xxx_charger {int /*<<< orphan*/  check_hw_failure_work; int /*<<< orphan*/  charger_wq; TYPE_2__ ac_chg; TYPE_1__ flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2xxx_charger_ovv_mngt(struct pm2xxx_charger *pm2, int val)
{
	dev_err(pm2->dev, "Overvoltage detected\n");
	pm2->flags.ovv = true;
	power_supply_changed(pm2->ac_chg.psy);

	/* Schedule a new HW failure check */
	queue_delayed_work(pm2->charger_wq, &pm2->check_hw_failure_work, 0);

	return 0;
}