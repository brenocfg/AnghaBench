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
struct sc27xx_fgu_data {int total_cap; int max_volt; int internal_resist; int min_volt; int table_len; int init_cap; int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; void* init_clbcnt; scalar_t__ base; int /*<<< orphan*/  battery; scalar_t__ alarm_cap; int /*<<< orphan*/  cap_table; } ;
struct power_supply_battery_ocv_table {int dummy; } ;
struct power_supply_battery_info {int charge_full_design_uah; int constant_charge_voltage_max_uv; int factory_internal_resistance_uohm; int voltage_min_design_uv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SC27XX_CLK_EN0 ; 
 scalar_t__ SC27XX_FGU_CLBCNT_DELTH ; 
 scalar_t__ SC27XX_FGU_CLBCNT_DELTL ; 
 int SC27XX_FGU_CLBCNT_MASK ; 
 int SC27XX_FGU_CLBCNT_SHIFT ; 
 int SC27XX_FGU_EN ; 
 scalar_t__ SC27XX_FGU_INT_CLR ; 
 int SC27XX_FGU_INT_MASK ; 
 scalar_t__ SC27XX_FGU_LOW_OVERLOAD ; 
 int SC27XX_FGU_LOW_OVERLOAD_MASK ; 
 int SC27XX_FGU_RTC_EN ; 
 scalar_t__ SC27XX_MODULE_EN0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_kmemdup (int /*<<< orphan*/ ,struct power_supply_battery_ocv_table*,int,int /*<<< orphan*/ ) ; 
 struct power_supply_battery_ocv_table* power_supply_find_ocv2cap_table (struct power_supply_battery_info*,int,int*) ; 
 int power_supply_get_battery_info (int /*<<< orphan*/ ,struct power_supply_battery_info*) ; 
 scalar_t__ power_supply_ocv2cap_simple (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  power_supply_put_battery_info (int /*<<< orphan*/ ,struct power_supply_battery_info*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int sc27xx_fgu_calibration (struct sc27xx_fgu_data*) ; 
 void* sc27xx_fgu_cap_to_clbcnt (struct sc27xx_fgu_data*,int) ; 
 int sc27xx_fgu_get_boot_capacity (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_set_clbcnt (struct sc27xx_fgu_data*,void*) ; 
 int sc27xx_fgu_voltage_to_adc (struct sc27xx_fgu_data*,int) ; 

__attribute__((used)) static int sc27xx_fgu_hw_init(struct sc27xx_fgu_data *data)
{
	struct power_supply_battery_info info = { };
	struct power_supply_battery_ocv_table *table;
	int ret, delta_clbcnt, alarm_adc;

	ret = power_supply_get_battery_info(data->battery, &info);
	if (ret) {
		dev_err(data->dev, "failed to get battery information\n");
		return ret;
	}

	data->total_cap = info.charge_full_design_uah / 1000;
	data->max_volt = info.constant_charge_voltage_max_uv / 1000;
	data->internal_resist = info.factory_internal_resistance_uohm / 1000;
	data->min_volt = info.voltage_min_design_uv;

	/*
	 * For SC27XX fuel gauge device, we only use one ocv-capacity
	 * table in normal temperature 20 Celsius.
	 */
	table = power_supply_find_ocv2cap_table(&info, 20, &data->table_len);
	if (!table)
		return -EINVAL;

	data->cap_table = devm_kmemdup(data->dev, table,
				       data->table_len * sizeof(*table),
				       GFP_KERNEL);
	if (!data->cap_table) {
		power_supply_put_battery_info(data->battery, &info);
		return -ENOMEM;
	}

	data->alarm_cap = power_supply_ocv2cap_simple(data->cap_table,
						      data->table_len,
						      data->min_volt);
	if (!data->alarm_cap)
		data->alarm_cap += 1;

	power_supply_put_battery_info(data->battery, &info);

	ret = sc27xx_fgu_calibration(data);
	if (ret)
		return ret;

	/* Enable the FGU module */
	ret = regmap_update_bits(data->regmap, SC27XX_MODULE_EN0,
				 SC27XX_FGU_EN, SC27XX_FGU_EN);
	if (ret) {
		dev_err(data->dev, "failed to enable fgu\n");
		return ret;
	}

	/* Enable the FGU RTC clock to make it work */
	ret = regmap_update_bits(data->regmap, SC27XX_CLK_EN0,
				 SC27XX_FGU_RTC_EN, SC27XX_FGU_RTC_EN);
	if (ret) {
		dev_err(data->dev, "failed to enable fgu RTC clock\n");
		goto disable_fgu;
	}

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_INT_CLR,
				 SC27XX_FGU_INT_MASK, SC27XX_FGU_INT_MASK);
	if (ret) {
		dev_err(data->dev, "failed to clear interrupt status\n");
		goto disable_clk;
	}

	/*
	 * Set the voltage low overload threshold, which means when the battery
	 * voltage is lower than this threshold, the controller will generate
	 * one interrupt to notify.
	 */
	alarm_adc = sc27xx_fgu_voltage_to_adc(data, data->min_volt / 1000);
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_LOW_OVERLOAD,
				 SC27XX_FGU_LOW_OVERLOAD_MASK, alarm_adc);
	if (ret) {
		dev_err(data->dev, "failed to set fgu low overload\n");
		goto disable_clk;
	}

	/*
	 * Set the coulomb counter delta threshold, that means when the coulomb
	 * counter change is multiples of the delta threshold, the controller
	 * will generate one interrupt to notify the users to update the battery
	 * capacity. Now we set the delta threshold as a counter value of 1%
	 * capacity.
	 */
	delta_clbcnt = sc27xx_fgu_cap_to_clbcnt(data, 1);

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_CLBCNT_DELTL,
				 SC27XX_FGU_CLBCNT_MASK, delta_clbcnt);
	if (ret) {
		dev_err(data->dev, "failed to set low delta coulomb counter\n");
		goto disable_clk;
	}

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_FGU_CLBCNT_DELTH,
				 SC27XX_FGU_CLBCNT_MASK,
				 delta_clbcnt >> SC27XX_FGU_CLBCNT_SHIFT);
	if (ret) {
		dev_err(data->dev, "failed to set high delta coulomb counter\n");
		goto disable_clk;
	}

	/*
	 * Get the boot battery capacity when system powers on, which is used to
	 * initialize the coulomb counter. After that, we can read the coulomb
	 * counter to measure the battery capacity.
	 */
	ret = sc27xx_fgu_get_boot_capacity(data, &data->init_cap);
	if (ret) {
		dev_err(data->dev, "failed to get boot capacity\n");
		goto disable_clk;
	}

	/*
	 * Convert battery capacity to the corresponding initial coulomb counter
	 * and set into coulomb counter registers.
	 */
	data->init_clbcnt = sc27xx_fgu_cap_to_clbcnt(data, data->init_cap);
	ret = sc27xx_fgu_set_clbcnt(data, data->init_clbcnt);
	if (ret) {
		dev_err(data->dev, "failed to initialize coulomb counter\n");
		goto disable_clk;
	}

	return 0;

disable_clk:
	regmap_update_bits(data->regmap, SC27XX_CLK_EN0, SC27XX_FGU_RTC_EN, 0);
disable_fgu:
	regmap_update_bits(data->regmap, SC27XX_MODULE_EN0, SC27XX_FGU_EN, 0);

	return ret;
}