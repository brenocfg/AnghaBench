#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int force_full; scalar_t__ fully_charged; int /*<<< orphan*/  charging; scalar_t__ low_bat; } ;
struct TYPE_6__ {int enable; int* cap_to_scale; int disable_cap_level; int /*<<< orphan*/  scaled_cap; } ;
struct TYPE_7__ {scalar_t__ level; scalar_t__ prev_level; int prev_percent; TYPE_2__ cap_scale; int /*<<< orphan*/  permille; scalar_t__ mah; scalar_t__ prev_mah; } ;
struct ab8500_fg {int /*<<< orphan*/  fg_kobject; TYPE_4__ flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  fg_psy; TYPE_3__ bat_cap; TYPE_1__* bm; } ;
struct TYPE_5__ {scalar_t__ capacity_scaling; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ab8500_fg_calculate_scaled_capacity (struct ab8500_fg*) ; 
 scalar_t__ ab8500_fg_capacity_level (struct ab8500_fg*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void ab8500_fg_check_capacity_limits(struct ab8500_fg *di, bool init)
{
	bool changed = false;
	int percent = DIV_ROUND_CLOSEST(di->bat_cap.permille, 10);

	di->bat_cap.level = ab8500_fg_capacity_level(di);

	if (di->bat_cap.level != di->bat_cap.prev_level) {
		/*
		 * We do not allow reported capacity level to go up
		 * unless we're charging or if we're in init
		 */
		if (!(!di->flags.charging && di->bat_cap.level >
			di->bat_cap.prev_level) || init) {
			dev_dbg(di->dev, "level changed from %d to %d\n",
				di->bat_cap.prev_level,
				di->bat_cap.level);
			di->bat_cap.prev_level = di->bat_cap.level;
			changed = true;
		} else {
			dev_dbg(di->dev, "level not allowed to go up "
				"since no charger is connected: %d to %d\n",
				di->bat_cap.prev_level,
				di->bat_cap.level);
		}
	}

	/*
	 * If we have received the LOW_BAT IRQ, set capacity to 0 to initiate
	 * shutdown
	 */
	if (di->flags.low_bat) {
		dev_dbg(di->dev, "Battery low, set capacity to 0\n");
		di->bat_cap.prev_percent = 0;
		di->bat_cap.permille = 0;
		percent = 0;
		di->bat_cap.prev_mah = 0;
		di->bat_cap.mah = 0;
		changed = true;
	} else if (di->flags.fully_charged) {
		/*
		 * We report 100% if algorithm reported fully charged
		 * and show 100% during maintenance charging (scaling).
		 */
		if (di->flags.force_full) {
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;

			if (!di->bat_cap.cap_scale.enable &&
						di->bm->capacity_scaling) {
				di->bat_cap.cap_scale.enable = true;
				di->bat_cap.cap_scale.cap_to_scale[0] = 100;
				di->bat_cap.cap_scale.cap_to_scale[1] =
						di->bat_cap.prev_percent;
				di->bat_cap.cap_scale.disable_cap_level = 100;
			}
		} else if (di->bat_cap.prev_percent != percent) {
			dev_dbg(di->dev,
				"battery reported full "
				"but capacity dropping: %d\n",
				percent);
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;
		}
	} else if (di->bat_cap.prev_percent != percent) {
		if (percent == 0) {
			/*
			 * We will not report 0% unless we've got
			 * the LOW_BAT IRQ, no matter what the FG
			 * algorithm says.
			 */
			di->bat_cap.prev_percent = 1;
			percent = 1;

			changed = true;
		} else if (!(!di->flags.charging &&
			percent > di->bat_cap.prev_percent) || init) {
			/*
			 * We do not allow reported capacity to go up
			 * unless we're charging or if we're in init
			 */
			dev_dbg(di->dev,
				"capacity changed from %d to %d (%d)\n",
				di->bat_cap.prev_percent,
				percent,
				di->bat_cap.permille);
			di->bat_cap.prev_percent = percent;
			di->bat_cap.prev_mah = di->bat_cap.mah;

			changed = true;
		} else {
			dev_dbg(di->dev, "capacity not allowed to go up since "
				"no charger is connected: %d to %d (%d)\n",
				di->bat_cap.prev_percent,
				percent,
				di->bat_cap.permille);
		}
	}

	if (changed) {
		if (di->bm->capacity_scaling) {
			di->bat_cap.cap_scale.scaled_cap =
				ab8500_fg_calculate_scaled_capacity(di);

			dev_info(di->dev, "capacity=%d (%d)\n",
				di->bat_cap.prev_percent,
				di->bat_cap.cap_scale.scaled_cap);
		}
		power_supply_changed(di->fg_psy);
		if (di->flags.fully_charged && di->flags.force_full) {
			dev_dbg(di->dev, "Battery full, notifying.\n");
			di->flags.force_full = false;
			sysfs_notify(&di->fg_kobject, NULL, "charge_full");
		}
		sysfs_notify(&di->fg_kobject, NULL, "charge_now");
	}
}