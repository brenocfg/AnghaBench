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
struct tps65132_regulator {int /*<<< orphan*/  dev; struct tps65132_reg_pdata* reg_pdata; } ;
struct tps65132_reg_pdata {int /*<<< orphan*/  act_dis_time_us; void* act_dis_gpiod; void* en_gpiod; } ;
struct regulator_desc {size_t id; } ;
struct regulator_config {struct tps65132_regulator* driver_data; } ;
struct device_node {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* devm_fwnode_get_index_gpiod_from_child (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps65132_of_parse_cb(struct device_node *np,
				const struct regulator_desc *desc,
				struct regulator_config *config)
{
	struct tps65132_regulator *tps = config->driver_data;
	struct tps65132_reg_pdata *rpdata = &tps->reg_pdata[desc->id];
	int ret;

	rpdata->en_gpiod = devm_fwnode_get_index_gpiod_from_child(tps->dev,
					"enable", 0, &np->fwnode, 0, "enable");
	if (IS_ERR_OR_NULL(rpdata->en_gpiod)) {
		ret = PTR_ERR(rpdata->en_gpiod);

		/* Ignore the error other than probe defer */
		if (ret == -EPROBE_DEFER)
			return ret;
		return 0;
	}

	rpdata->act_dis_gpiod = devm_fwnode_get_index_gpiod_from_child(
					tps->dev, "active-discharge", 0,
					&np->fwnode, 0, "active-discharge");
	if (IS_ERR_OR_NULL(rpdata->act_dis_gpiod)) {
		ret = PTR_ERR(rpdata->act_dis_gpiod);

		/* Ignore the error other than probe defer */
		if (ret == -EPROBE_DEFER)
			return ret;

		return 0;
	}

	ret = of_property_read_u32(np, "ti,active-discharge-time-us",
				   &rpdata->act_dis_time_us);
	if (ret < 0) {
		dev_err(tps->dev, "Failed to read active discharge time:%d\n",
			ret);
		return ret;
	}

	return 0;
}