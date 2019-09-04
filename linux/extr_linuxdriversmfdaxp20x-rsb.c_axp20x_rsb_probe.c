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
struct sunxi_rsb_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  regmap_cfg; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int axp20x_device_probe (struct axp20x_dev*) ; 
 int axp20x_match_device (struct axp20x_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct axp20x_dev*) ; 
 struct axp20x_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_sunxi_rsb (struct sunxi_rsb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_rsb_probe(struct sunxi_rsb_device *rdev)
{
	struct axp20x_dev *axp20x;
	int ret;

	axp20x = devm_kzalloc(&rdev->dev, sizeof(*axp20x), GFP_KERNEL);
	if (!axp20x)
		return -ENOMEM;

	axp20x->dev = &rdev->dev;
	axp20x->irq = rdev->irq;
	dev_set_drvdata(&rdev->dev, axp20x);

	ret = axp20x_match_device(axp20x);
	if (ret)
		return ret;

	axp20x->regmap = devm_regmap_init_sunxi_rsb(rdev, axp20x->regmap_cfg);
	if (IS_ERR(axp20x->regmap)) {
		ret = PTR_ERR(axp20x->regmap);
		dev_err(&rdev->dev, "regmap init failed: %d\n", ret);
		return ret;
	}

	return axp20x_device_probe(axp20x);
}