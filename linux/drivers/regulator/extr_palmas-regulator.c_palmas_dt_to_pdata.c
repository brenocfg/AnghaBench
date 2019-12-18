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
typedef  int /*<<< orphan*/  u32 ;
struct palmas_reg_init {int roof_floor; int /*<<< orphan*/  vsel; int /*<<< orphan*/  mode_sleep; void* warm_reset; } ;
struct palmas_pmic_platform_data {void* ldo6_vibrator; void* enable_ldo8_tracking; struct palmas_reg_init** reg_init; scalar_t__* reg_data; } ;
struct palmas_pmic_driver_data {int max_reg; struct of_regulator_match* palmas_matches; } ;
struct of_regulator_match {int /*<<< orphan*/  name; scalar_t__ init_data; struct device_node* of_node; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PALMAS_EXT_CONTROL_ENABLE1 ; 
 int PALMAS_EXT_CONTROL_ENABLE2 ; 
 int PALMAS_EXT_CONTROL_NSLEEP ; 
 int PALMAS_REG_LDO8 ; 
 int /*<<< orphan*/  PALMAS_SMPS12_VOLTAGE_RANGE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct palmas_reg_init* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_regulator_match (struct device*,struct device_node*,struct of_regulator_match*,int) ; 

__attribute__((used)) static int palmas_dt_to_pdata(struct device *dev,
			      struct device_node *node,
			      struct palmas_pmic_platform_data *pdata,
			      struct palmas_pmic_driver_data *ddata)
{
	struct device_node *regulators;
	u32 prop;
	int idx, ret;

	regulators = of_get_child_by_name(node, "regulators");
	if (!regulators) {
		dev_info(dev, "regulator node not found\n");
		return 0;
	}

	ret = of_regulator_match(dev, regulators, ddata->palmas_matches,
				 ddata->max_reg);
	of_node_put(regulators);
	if (ret < 0) {
		dev_err(dev, "Error parsing regulator init data: %d\n", ret);
		return 0;
	}

	for (idx = 0; idx < ddata->max_reg; idx++) {
		struct of_regulator_match *match;
		struct palmas_reg_init *rinit;
		struct device_node *np;

		match = &ddata->palmas_matches[idx];
		np = match->of_node;

		if (!match->init_data || !np)
			continue;

		rinit = devm_kzalloc(dev, sizeof(*rinit), GFP_KERNEL);
		if (!rinit)
			return -ENOMEM;

		pdata->reg_data[idx] = match->init_data;
		pdata->reg_init[idx] = rinit;

		rinit->warm_reset = of_property_read_bool(np, "ti,warm-reset");
		ret = of_property_read_u32(np, "ti,roof-floor", &prop);
		/* EINVAL: Property not found */
		if (ret != -EINVAL) {
			int econtrol;

			/* use default value, when no value is specified */
			econtrol = PALMAS_EXT_CONTROL_NSLEEP;
			if (!ret) {
				switch (prop) {
				case 1:
					econtrol = PALMAS_EXT_CONTROL_ENABLE1;
					break;
				case 2:
					econtrol = PALMAS_EXT_CONTROL_ENABLE2;
					break;
				case 3:
					econtrol = PALMAS_EXT_CONTROL_NSLEEP;
					break;
				default:
					WARN_ON(1);
					dev_warn(dev,
						 "%s: Invalid roof-floor option: %u\n",
						 match->name, prop);
					break;
				}
			}
			rinit->roof_floor = econtrol;
		}

		ret = of_property_read_u32(np, "ti,mode-sleep", &prop);
		if (!ret)
			rinit->mode_sleep = prop;

		ret = of_property_read_bool(np, "ti,smps-range");
		if (ret)
			rinit->vsel = PALMAS_SMPS12_VOLTAGE_RANGE;

		if (idx == PALMAS_REG_LDO8)
			pdata->enable_ldo8_tracking = of_property_read_bool(
						np, "ti,enable-ldo8-tracking");
	}

	pdata->ldo6_vibrator = of_property_read_bool(node, "ti,ldo6-vibrator");

	return 0;
}