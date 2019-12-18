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
union power_supply_propval {int intval; } ;
typedef  scalar_t__ u8 ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_CCC ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_POC ; 
 int /*<<< orphan*/  BQ24190_REG_POC_CHG_CONFIG_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_POC_CHG_CONFIG_SHIFT ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 int bq24190_read_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int bq24190_charger_get_charge_type(struct bq24190_dev_info *bdi,
		union power_supply_propval *val)
{
	u8 v;
	int type, ret;

	ret = bq24190_read_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_CHG_CONFIG_MASK,
			BQ24190_REG_POC_CHG_CONFIG_SHIFT,
			&v);
	if (ret < 0)
		return ret;

	/* If POC[CHG_CONFIG] (REG01[5:4]) == 0, charge is disabled */
	if (!v) {
		type = POWER_SUPPLY_CHARGE_TYPE_NONE;
	} else {
		ret = bq24190_read_mask(bdi, BQ24190_REG_CCC,
				BQ24190_REG_CCC_FORCE_20PCT_MASK,
				BQ24190_REG_CCC_FORCE_20PCT_SHIFT,
				&v);
		if (ret < 0)
			return ret;

		type = (v) ? POWER_SUPPLY_CHARGE_TYPE_TRICKLE :
			     POWER_SUPPLY_CHARGE_TYPE_FAST;
	}

	val->intval = type;

	return 0;
}