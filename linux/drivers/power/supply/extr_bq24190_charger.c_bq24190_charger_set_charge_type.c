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
typedef  int u8 ;
struct bq24190_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ24190_REG_CCC ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_CCC_FORCE_20PCT_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_CTTC ; 
 int /*<<< orphan*/  BQ24190_REG_CTTC_EN_TERM_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_CTTC_EN_TERM_SHIFT ; 
 int /*<<< orphan*/  BQ24190_REG_POC ; 
 int /*<<< orphan*/  BQ24190_REG_POC_CHG_CONFIG_MASK ; 
 int /*<<< orphan*/  BQ24190_REG_POC_CHG_CONFIG_SHIFT ; 
 int EINVAL ; 
#define  POWER_SUPPLY_CHARGE_TYPE_FAST 130 
#define  POWER_SUPPLY_CHARGE_TYPE_NONE 129 
#define  POWER_SUPPLY_CHARGE_TYPE_TRICKLE 128 
 int bq24190_write_mask (struct bq24190_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bq24190_charger_set_charge_type(struct bq24190_dev_info *bdi,
		const union power_supply_propval *val)
{
	u8 chg_config, force_20pct, en_term;
	int ret;

	/*
	 * According to the "Termination when REG02[0] = 1" section of
	 * the bq24190 manual, the trickle charge could be less than the
	 * termination current so it recommends turning off the termination
	 * function.
	 *
	 * Note: AFAICT from the datasheet, the user will have to manually
	 * turn off the charging when in 20% mode.  If its not turned off,
	 * there could be battery damage.  So, use this mode at your own risk.
	 */
	switch (val->intval) {
	case POWER_SUPPLY_CHARGE_TYPE_NONE:
		chg_config = 0x0;
		break;
	case POWER_SUPPLY_CHARGE_TYPE_TRICKLE:
		chg_config = 0x1;
		force_20pct = 0x1;
		en_term = 0x0;
		break;
	case POWER_SUPPLY_CHARGE_TYPE_FAST:
		chg_config = 0x1;
		force_20pct = 0x0;
		en_term = 0x1;
		break;
	default:
		return -EINVAL;
	}

	if (chg_config) { /* Enabling the charger */
		ret = bq24190_write_mask(bdi, BQ24190_REG_CCC,
				BQ24190_REG_CCC_FORCE_20PCT_MASK,
				BQ24190_REG_CCC_FORCE_20PCT_SHIFT,
				force_20pct);
		if (ret < 0)
			return ret;

		ret = bq24190_write_mask(bdi, BQ24190_REG_CTTC,
				BQ24190_REG_CTTC_EN_TERM_MASK,
				BQ24190_REG_CTTC_EN_TERM_SHIFT,
				en_term);
		if (ret < 0)
			return ret;
	}

	return bq24190_write_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_CHG_CONFIG_MASK,
			BQ24190_REG_POC_CHG_CONFIG_SHIFT, chg_config);
}