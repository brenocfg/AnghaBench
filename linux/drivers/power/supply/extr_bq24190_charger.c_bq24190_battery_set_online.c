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
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_MOC ; 
 int /*<<< orphan*/  BQ24190_REG_MOC_BATFET_DISABLE_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_MOC_BATFET_DISABLE_SHIFT ; 
 int bq24190_write_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bq24190_battery_set_online(struct bq24190_dev_info *bdi,
		const union power_supply_propval *val)
{
	return bq24190_write_mask(bdi, BQ24190_REG_MOC,
			BQ24190_REG_MOC_BATFET_DISABLE_MASK,
			BQ24190_REG_MOC_BATFET_DISABLE_SHIFT, !val->intval);
}