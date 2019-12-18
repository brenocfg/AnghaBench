#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct regulator_init_data {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  name; } ;
struct regulator_config {struct device_node* of_node; struct mc13xxx_regulator_priv* driver_data; struct regulator_init_data* init_data; TYPE_4__* dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct mc13xxx_regulator_priv {int num_regulators; int /*<<< orphan*/ * regulators; struct mc13xxx* mc13xxx; TYPE_2__* mc13xxx_regulators; } ;
struct mc13xxx_regulator_platform_data {int num_regulators; TYPE_1__* regulators; } ;
struct mc13xxx_regulator_init_data {int id; struct device_node* node; struct regulator_init_data* init_data; } ;
struct mc13xxx {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {struct regulator_desc desc; } ;
struct TYPE_9__ {int id; struct regulator_init_data* init_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 struct mc13xxx* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct mc13xxx_regulator_platform_data* dev_get_platdata (TYPE_4__*) ; 
 struct mc13xxx_regulator_priv* devm_kzalloc (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_4__*,struct regulator_desc*,struct regulator_config*) ; 
 TYPE_2__* mc13783_regulators ; 
 int mc13xxx_get_num_regulators_dt (struct platform_device*) ; 
 struct mc13xxx_regulator_init_data* mc13xxx_parse_regulators_dt (struct platform_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mc13xxx_regulator_priv*) ; 
 int /*<<< orphan*/  regulators ; 
 int /*<<< orphan*/  struct_size (struct mc13xxx_regulator_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mc13783_regulator_probe(struct platform_device *pdev)
{
	struct mc13xxx_regulator_priv *priv;
	struct mc13xxx *mc13783 = dev_get_drvdata(pdev->dev.parent);
	struct mc13xxx_regulator_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct mc13xxx_regulator_init_data *mc13xxx_data;
	struct regulator_config config = { };
	int i, num_regulators;

	num_regulators = mc13xxx_get_num_regulators_dt(pdev);

	if (num_regulators <= 0 && pdata)
		num_regulators = pdata->num_regulators;
	if (num_regulators <= 0)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev,
			    struct_size(priv, regulators, num_regulators),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->num_regulators = num_regulators;
	priv->mc13xxx_regulators = mc13783_regulators;
	priv->mc13xxx = mc13783;
	platform_set_drvdata(pdev, priv);

	mc13xxx_data = mc13xxx_parse_regulators_dt(pdev, mc13783_regulators,
					ARRAY_SIZE(mc13783_regulators));

	for (i = 0; i < priv->num_regulators; i++) {
		struct regulator_init_data *init_data;
		struct regulator_desc *desc;
		struct device_node *node = NULL;
		int id;

		if (mc13xxx_data) {
			id = mc13xxx_data[i].id;
			init_data = mc13xxx_data[i].init_data;
			node = mc13xxx_data[i].node;
		} else {
			id = pdata->regulators[i].id;
			init_data = pdata->regulators[i].init_data;
		}
		desc = &mc13783_regulators[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.driver_data = priv;
		config.of_node = node;

		priv->regulators[i] = devm_regulator_register(&pdev->dev, desc,
							      &config);
		if (IS_ERR(priv->regulators[i])) {
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				mc13783_regulators[i].desc.name);
			return PTR_ERR(priv->regulators[i]);
		}
	}

	return 0;
}