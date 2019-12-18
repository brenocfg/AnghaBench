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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct device_node* of_node; struct ab8500_regulator_info* driver_data; struct regulator_init_data* init_data; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  name; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  n_voltages; } ;
struct ab8500_regulator_info {int voltage_mask; TYPE_2__ desc; TYPE_1__* dev; } ;
struct ab8500 {int dummy; } ;
struct TYPE_7__ {struct ab8500_regulator_info* info; } ;

/* Variables and functions */
 scalar_t__ AB8500_LDO_AUX3 ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 TYPE_4__ abx500_regulator ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 scalar_t__ is_ab8500_1p1_or_earlier (struct ab8500*) ; 
 int /*<<< orphan*/  ldo_vauxn_voltages ; 

__attribute__((used)) static int ab8500_regulator_register(struct platform_device *pdev,
				     struct regulator_init_data *init_data,
				     int id, struct device_node *np)
{
	struct ab8500 *ab8500 = dev_get_drvdata(pdev->dev.parent);
	struct ab8500_regulator_info *info = NULL;
	struct regulator_config config = { };
	struct regulator_dev *rdev;

	/* assign per-regulator data */
	info = &abx500_regulator.info[id];
	info->dev = &pdev->dev;

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = info;
	config.of_node = np;

	/* fix for hardware before ab8500v2.0 */
	if (is_ab8500_1p1_or_earlier(ab8500)) {
		if (info->desc.id == AB8500_LDO_AUX3) {
			info->desc.n_voltages =
				ARRAY_SIZE(ldo_vauxn_voltages);
			info->desc.volt_table = ldo_vauxn_voltages;
			info->voltage_mask = 0xf;
		}
	}

	/* register regulator with framework */
	rdev = devm_regulator_register(&pdev->dev, &info->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "failed to register regulator %s\n",
			info->desc.name);
		return PTR_ERR(rdev);
	}

	return 0;
}