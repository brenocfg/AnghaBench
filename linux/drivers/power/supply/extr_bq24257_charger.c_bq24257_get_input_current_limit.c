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
struct bq24257_device {int dummy; } ;

/* Variables and functions */
 int BQ24257_IILIMIT_MAP_SIZE ; 
 int ENODATA ; 
 int /*<<< orphan*/  F_IILIMIT ; 
 int bq24257_field_read (struct bq24257_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bq24257_iilimit_map ; 

__attribute__((used)) static int bq24257_get_input_current_limit(struct bq24257_device *bq,
					   union power_supply_propval *val)
{
	int ret;

	ret = bq24257_field_read(bq, F_IILIMIT);
	if (ret < 0)
		return ret;

	/*
	 * The "External ILIM" and "Production & Test" modes are not exposed
	 * through this driver and not being covered by the lookup table.
	 * Should such a mode have become active let's return an error rather
	 * than exceeding the bounds of the lookup table and returning
	 * garbage.
	 */
	if (ret >= BQ24257_IILIMIT_MAP_SIZE)
		return -ENODATA;

	val->intval = bq24257_iilimit_map[ret];

	return 0;
}