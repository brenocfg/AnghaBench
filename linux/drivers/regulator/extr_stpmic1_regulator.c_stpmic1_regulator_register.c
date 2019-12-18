#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct stpmic1_regulator_cfg {scalar_t__ mask_reset_reg; int /*<<< orphan*/  mask_reset_mask; TYPE_3__ desc; } ;
struct stpmic1 {int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  of_node; void* driver_data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  init_data; TYPE_1__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct of_regulator_match {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct stpmic1* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_config*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct regulator_dev*) ; 
 scalar_t__ of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int of_irq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stpmic1_curlim_irq_handler ; 

__attribute__((used)) static int stpmic1_regulator_register(struct platform_device *pdev, int id,
				      struct of_regulator_match *match,
				      const struct stpmic1_regulator_cfg *cfg)
{
	struct stpmic1 *pmic_dev = dev_get_drvdata(pdev->dev.parent);
	struct regulator_dev *rdev;
	struct regulator_config config = {};
	int ret = 0;
	int irq;

	config.dev = &pdev->dev;
	config.init_data = match->init_data;
	config.of_node = match->of_node;
	config.regmap = pmic_dev->regmap;
	config.driver_data = (void *)cfg;

	rdev = devm_regulator_register(&pdev->dev, &cfg->desc, &config);
	if (IS_ERR(rdev)) {
		dev_err(&pdev->dev, "failed to register %s regulator\n",
			cfg->desc.name);
		return PTR_ERR(rdev);
	}

	/* set mask reset */
	if (of_get_property(config.of_node, "st,mask-reset", NULL) &&
	    cfg->mask_reset_reg != 0) {
		ret = regmap_update_bits(pmic_dev->regmap,
					 cfg->mask_reset_reg,
					 cfg->mask_reset_mask,
					 cfg->mask_reset_mask);
		if (ret) {
			dev_err(&pdev->dev, "set mask reset failed\n");
			return ret;
		}
	}

	/* setup an irq handler for over-current detection */
	irq = of_irq_get(config.of_node, 0);
	if (irq > 0) {
		ret = devm_request_threaded_irq(&pdev->dev,
						irq, NULL,
						stpmic1_curlim_irq_handler,
						IRQF_ONESHOT | IRQF_SHARED,
						pdev->name, rdev);
		if (ret) {
			dev_err(&pdev->dev, "Request IRQ failed\n");
			return ret;
		}
	}
	return 0;
}