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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct bq24257_device {int /*<<< orphan*/  iilimit_setup_work; scalar_t__ iilimit_autoset_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24257_IILIMIT_MAP_SIZE ; 
 int /*<<< orphan*/  F_IILIMIT ; 
 int bq24257_field_write (struct bq24257_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq24257_find_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq24257_iilimit_map ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq24257_set_input_current_limit(struct bq24257_device *bq,
					const union power_supply_propval *val)
{
	/*
	 * Address the case where the user manually sets an input current limit
	 * while the charger auto-detection mechanism is is active. In this
	 * case we want to abort and go straight to the user-specified value.
	 */
	if (bq->iilimit_autoset_enable)
		cancel_delayed_work_sync(&bq->iilimit_setup_work);

	return bq24257_field_write(bq, F_IILIMIT,
				   bq24257_find_idx(val->intval,
						    bq24257_iilimit_map,
						    BQ24257_IILIMIT_MAP_SIZE));
}