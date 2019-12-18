#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_regulator_match {scalar_t__ init_data; } ;
struct device_node {int dummy; } ;
struct da9063_regulators_pdata {int n_regulators; struct da9063_regulator_data* regulator_data; } ;
struct da9063_regulator_data {int id; scalar_t__ initdata; } ;
struct da9063 {scalar_t__ type; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct of_regulator_match*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct da9063_regulators_pdata* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PMIC_TYPE_DA9063L ; 
 struct of_regulator_match* da9063_matches ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct da9063* dev_get_drvdata (TYPE_4__*) ; 
 struct da9063_regulator_data* devm_kcalloc (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 struct da9063_regulators_pdata* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_regulator_match (TYPE_1__*,struct device_node*,struct of_regulator_match*,int) ; 

__attribute__((used)) static struct da9063_regulators_pdata *da9063_parse_regulators_dt(
		struct platform_device *pdev,
		struct of_regulator_match **da9063_reg_matches)
{
	struct da9063 *da9063 = dev_get_drvdata(pdev->dev.parent);
	struct da9063_regulators_pdata *pdata;
	struct da9063_regulator_data *rdata;
	struct device_node *node;
	int da9063_matches_len = ARRAY_SIZE(da9063_matches);
	int i, n, num;

	if (da9063->type == PMIC_TYPE_DA9063L)
		da9063_matches_len -= 6;

	node = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	if (!node) {
		dev_err(&pdev->dev, "Regulators device node not found\n");
		return ERR_PTR(-ENODEV);
	}

	num = of_regulator_match(&pdev->dev, node, da9063_matches,
				 da9063_matches_len);
	of_node_put(node);
	if (num < 0) {
		dev_err(&pdev->dev, "Failed to match regulators\n");
		return ERR_PTR(-EINVAL);
	}

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	pdata->regulator_data = devm_kcalloc(&pdev->dev,
					num, sizeof(*pdata->regulator_data),
					GFP_KERNEL);
	if (!pdata->regulator_data)
		return ERR_PTR(-ENOMEM);
	pdata->n_regulators = num;

	n = 0;
	for (i = 0; i < da9063_matches_len; i++) {
		if (!da9063_matches[i].init_data)
			continue;

		rdata = &pdata->regulator_data[n];
		rdata->id = i;
		rdata->initdata = da9063_matches[i].init_data;

		n++;
	}

	*da9063_reg_matches = da9063_matches;
	return pdata;
}