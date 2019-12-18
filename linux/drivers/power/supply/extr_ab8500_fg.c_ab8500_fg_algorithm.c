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
struct TYPE_4__ {scalar_t__ charging; scalar_t__ calibrate; } ;
struct TYPE_3__ {int /*<<< orphan*/  prev_level; int /*<<< orphan*/  prev_percent; int /*<<< orphan*/  prev_mah; int /*<<< orphan*/  level; int /*<<< orphan*/  permille; int /*<<< orphan*/  mah; int /*<<< orphan*/  max_mah; int /*<<< orphan*/  max_mah_design; } ;
struct ab8500_fg {int /*<<< orphan*/  recovery_needed; int /*<<< orphan*/  high_curr_mode; int /*<<< orphan*/  discharge_state; int /*<<< orphan*/  charge_state; TYPE_2__ flags; int /*<<< orphan*/  accu_charge; int /*<<< orphan*/  avg_curr; int /*<<< orphan*/  inst_curr; int /*<<< orphan*/  vbat; TYPE_1__ bat_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ab8500_fg_algorithm_calibrate (struct ab8500_fg*) ; 
 int /*<<< orphan*/  ab8500_fg_algorithm_charging (struct ab8500_fg*) ; 
 int /*<<< orphan*/  ab8500_fg_algorithm_discharging (struct ab8500_fg*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ab8500_fg_algorithm(struct ab8500_fg *di)
{
	if (di->flags.calibrate)
		ab8500_fg_algorithm_calibrate(di);
	else {
		if (di->flags.charging)
			ab8500_fg_algorithm_charging(di);
		else
			ab8500_fg_algorithm_discharging(di);
	}

	dev_dbg(di->dev, "[FG_DATA] %d %d %d %d %d %d %d %d %d %d "
		"%d %d %d %d %d %d %d\n",
		di->bat_cap.max_mah_design,
		di->bat_cap.max_mah,
		di->bat_cap.mah,
		di->bat_cap.permille,
		di->bat_cap.level,
		di->bat_cap.prev_mah,
		di->bat_cap.prev_percent,
		di->bat_cap.prev_level,
		di->vbat,
		di->inst_curr,
		di->avg_curr,
		di->accu_charge,
		di->flags.charging,
		di->charge_state,
		di->discharge_state,
		di->high_curr_mode,
		di->recovery_needed);
}