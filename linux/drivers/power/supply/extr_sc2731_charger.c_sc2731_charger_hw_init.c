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
typedef  int u32 ;
struct sc2731_charger_info {int /*<<< orphan*/  regmap; scalar_t__ base; int /*<<< orphan*/  psy_usb; int /*<<< orphan*/  dev; } ;
struct power_supply_battery_info {int charge_term_current_ua; int constant_charge_voltage_max_uv; } ;

/* Variables and functions */
 int SC2731_CHARGE_EN ; 
 scalar_t__ SC2731_CHG_CFG0 ; 
 scalar_t__ SC2731_CHG_CFG2 ; 
 scalar_t__ SC2731_MODULE_EN1 ; 
 int SC2731_TERMINATION_CUR_MASK ; 
 int SC2731_TERMINATION_VOL_CAL_MASK ; 
 int SC2731_TERMINATION_VOL_CAL_SHIFT ; 
 int SC2731_TERMINATION_VOL_MASK ; 
 int SC2731_TERMINATION_VOL_SHIFT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int power_supply_get_battery_info (int /*<<< orphan*/ ,struct power_supply_battery_info*) ; 
 int /*<<< orphan*/  power_supply_put_battery_info (int /*<<< orphan*/ ,struct power_supply_battery_info*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int sc2731_charger_hw_init(struct sc2731_charger_info *info)
{
	struct power_supply_battery_info bat_info = { };
	u32 term_currrent, term_voltage, cur_val, vol_val;
	int ret;

	/* Enable charger module */
	ret = regmap_update_bits(info->regmap, SC2731_MODULE_EN1,
				 SC2731_CHARGE_EN, SC2731_CHARGE_EN);
	if (ret)
		return ret;

	ret = power_supply_get_battery_info(info->psy_usb, &bat_info);
	if (ret) {
		dev_warn(info->dev, "no battery information is supplied\n");

		/*
		 * If no battery information is supplied, we should set
		 * default charge termination current to 120 mA, and default
		 * charge termination voltage to 4.35V.
		 */
		cur_val = 0x2;
		vol_val = 0x1;
	} else {
		term_currrent = bat_info.charge_term_current_ua / 1000;

		if (term_currrent <= 90)
			cur_val = 0;
		else if (term_currrent >= 265)
			cur_val = 0x7;
		else
			cur_val = ((term_currrent - 90) / 25) + 1;

		term_voltage = bat_info.constant_charge_voltage_max_uv / 1000;

		if (term_voltage > 4500)
			term_voltage = 4500;

		if (term_voltage > 4200)
			vol_val = (term_voltage - 4200) / 100;
		else
			vol_val = 0;

		power_supply_put_battery_info(info->psy_usb, &bat_info);
	}

	/* Set charge termination current */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG2,
				 SC2731_TERMINATION_CUR_MASK, cur_val);
	if (ret)
		goto error;

	/* Set charge termination voltage */
	ret = regmap_update_bits(info->regmap, info->base + SC2731_CHG_CFG0,
				 SC2731_TERMINATION_VOL_MASK |
				 SC2731_TERMINATION_VOL_CAL_MASK,
				 (vol_val << SC2731_TERMINATION_VOL_SHIFT) |
				 (0x6 << SC2731_TERMINATION_VOL_CAL_SHIFT));
	if (ret)
		goto error;

	return 0;

error:
	regmap_update_bits(info->regmap, SC2731_MODULE_EN1, SC2731_CHARGE_EN, 0);
	return ret;
}