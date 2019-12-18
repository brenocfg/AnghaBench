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
struct charger_manager {int charger_enabled; int /*<<< orphan*/  dev; void* charging_end_time; void* charging_start_time; scalar_t__ emergency_stop; struct charger_desc* desc; } ;
struct charger_desc {int num_charger_regulators; TYPE_1__* charger_regulators; } ;
struct TYPE_2__ {int /*<<< orphan*/  regulator_name; int /*<<< orphan*/  consumer; scalar_t__ externally_control; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 void* ktime_to_ms (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_force_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ regulator_is_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_charger_enable(struct charger_manager *cm, bool enable)
{
	int err = 0, i;
	struct charger_desc *desc = cm->desc;

	/* Ignore if it's redundant command */
	if (enable == cm->charger_enabled)
		return 0;

	if (enable) {
		if (cm->emergency_stop)
			return -EAGAIN;

		/*
		 * Save start time of charging to limit
		 * maximum possible charging time.
		 */
		cm->charging_start_time = ktime_to_ms(ktime_get());
		cm->charging_end_time = 0;

		for (i = 0 ; i < desc->num_charger_regulators ; i++) {
			if (desc->charger_regulators[i].externally_control)
				continue;

			err = regulator_enable(desc->charger_regulators[i].consumer);
			if (err < 0) {
				dev_warn(cm->dev, "Cannot enable %s regulator\n",
					 desc->charger_regulators[i].regulator_name);
			}
		}
	} else {
		/*
		 * Save end time of charging to maintain fully charged state
		 * of battery after full-batt.
		 */
		cm->charging_start_time = 0;
		cm->charging_end_time = ktime_to_ms(ktime_get());

		for (i = 0 ; i < desc->num_charger_regulators ; i++) {
			if (desc->charger_regulators[i].externally_control)
				continue;

			err = regulator_disable(desc->charger_regulators[i].consumer);
			if (err < 0) {
				dev_warn(cm->dev, "Cannot disable %s regulator\n",
					 desc->charger_regulators[i].regulator_name);
			}
		}

		/*
		 * Abnormal battery state - Stop charging forcibly,
		 * even if charger was enabled at the other places
		 */
		for (i = 0; i < desc->num_charger_regulators; i++) {
			if (regulator_is_enabled(
				    desc->charger_regulators[i].consumer)) {
				regulator_force_disable(
					desc->charger_regulators[i].consumer);
				dev_warn(cm->dev, "Disable regulator(%s) forcibly\n",
					 desc->charger_regulators[i].regulator_name);
			}
		}
	}

	if (!err)
		cm->charger_enabled = enable;

	return err;
}