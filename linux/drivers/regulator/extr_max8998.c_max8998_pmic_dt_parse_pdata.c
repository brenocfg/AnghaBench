#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct max8998_regulator_data {struct device_node* reg_node; int /*<<< orphan*/  initdata; int /*<<< orphan*/  id; } ;
struct max8998_platform_data {int num_regulators; int buck_voltage_lock; int buck1_default_idx; int buck2_default_idx; TYPE_1__* buck2_voltage; TYPE_1__* buck1_voltage; struct max8998_regulator_data* regulators; } ;
struct max8998_dev {TYPE_3__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 struct max8998_regulator_data* devm_kcalloc (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int max8998_pmic_dt_parse_dvs_gpio (struct max8998_dev*,struct max8998_platform_data*,struct device_node*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_get_child_count (struct device_node*) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (TYPE_3__*,struct device_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,TYPE_1__*,unsigned int) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int max8998_pmic_dt_parse_pdata(struct max8998_dev *iodev,
					struct max8998_platform_data *pdata)
{
	struct device_node *pmic_np = iodev->dev->of_node;
	struct device_node *regulators_np, *reg_np;
	struct max8998_regulator_data *rdata;
	unsigned int i;
	int ret;

	regulators_np = of_get_child_by_name(pmic_np, "regulators");
	if (!regulators_np) {
		dev_err(iodev->dev, "could not find regulators sub-node\n");
		return -EINVAL;
	}

	/* count the number of regulators to be supported in pmic */
	pdata->num_regulators = of_get_child_count(regulators_np);

	rdata = devm_kcalloc(iodev->dev,
			     pdata->num_regulators, sizeof(*rdata),
			     GFP_KERNEL);
	if (!rdata) {
		of_node_put(regulators_np);
		return -ENOMEM;
	}

	pdata->regulators = rdata;
	for (i = 0; i < ARRAY_SIZE(regulators); ++i) {
		reg_np = of_get_child_by_name(regulators_np,
							regulators[i].name);
		if (!reg_np)
			continue;

		rdata->id = regulators[i].id;
		rdata->initdata = of_get_regulator_init_data(iodev->dev,
							     reg_np,
							     &regulators[i]);
		rdata->reg_node = reg_np;
		++rdata;
	}
	pdata->num_regulators = rdata - pdata->regulators;

	of_node_put(reg_np);
	of_node_put(regulators_np);

	ret = max8998_pmic_dt_parse_dvs_gpio(iodev, pdata, pmic_np);
	if (ret)
		return -EINVAL;

	if (of_find_property(pmic_np, "max8998,pmic-buck-voltage-lock", NULL))
		pdata->buck_voltage_lock = true;

	ret = of_property_read_u32(pmic_np,
					"max8998,pmic-buck1-default-dvs-idx",
					&pdata->buck1_default_idx);
	if (!ret && pdata->buck1_default_idx >= 4) {
		pdata->buck1_default_idx = 0;
		dev_warn(iodev->dev, "invalid value for default dvs index, using 0 instead\n");
	}

	ret = of_property_read_u32(pmic_np,
					"max8998,pmic-buck2-default-dvs-idx",
					&pdata->buck2_default_idx);
	if (!ret && pdata->buck2_default_idx >= 2) {
		pdata->buck2_default_idx = 0;
		dev_warn(iodev->dev, "invalid value for default dvs index, using 0 instead\n");
	}

	ret = of_property_read_u32_array(pmic_np,
					"max8998,pmic-buck1-dvs-voltage",
					pdata->buck1_voltage,
					ARRAY_SIZE(pdata->buck1_voltage));
	if (ret) {
		dev_err(iodev->dev, "buck1 voltages not specified\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_array(pmic_np,
					"max8998,pmic-buck2-dvs-voltage",
					pdata->buck2_voltage,
					ARRAY_SIZE(pdata->buck2_voltage));
	if (ret) {
		dev_err(iodev->dev, "buck2 voltages not specified\n");
		return -EINVAL;
	}

	return 0;
}