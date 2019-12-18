#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_6__ {int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; TYPE_3__* dev; } ;
struct mxs_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct mxs_pwm_chip* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_pwm_ops ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mxs_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  pwmchip_remove (TYPE_1__*) ; 
 int stmp_reset_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxs_pwm_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct mxs_pwm_chip *mxs;
	int ret;

	mxs = devm_kzalloc(&pdev->dev, sizeof(*mxs), GFP_KERNEL);
	if (!mxs)
		return -ENOMEM;

	mxs->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(mxs->base))
		return PTR_ERR(mxs->base);

	mxs->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(mxs->clk))
		return PTR_ERR(mxs->clk);

	mxs->chip.dev = &pdev->dev;
	mxs->chip.ops = &mxs_pwm_ops;
	mxs->chip.base = -1;

	ret = of_property_read_u32(np, "fsl,pwm-number", &mxs->chip.npwm);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to get pwm number: %d\n", ret);
		return ret;
	}

	ret = pwmchip_add(&mxs->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add pwm chip %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, mxs);

	ret = stmp_reset_block(mxs->base);
	if (ret)
		goto pwm_remove;

	return 0;

pwm_remove:
	pwmchip_remove(&mxs->chip);
	return ret;
}