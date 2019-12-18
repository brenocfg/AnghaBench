#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct sprd_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/  num_pwms; int /*<<< orphan*/ * dev; int /*<<< orphan*/  base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct sprd_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sprd_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int sprd_pwm_clk_init (struct sprd_pwm_chip*) ; 
 int /*<<< orphan*/  sprd_pwm_ops ; 

__attribute__((used)) static int sprd_pwm_probe(struct platform_device *pdev)
{
	struct sprd_pwm_chip *spc;
	int ret;

	spc = devm_kzalloc(&pdev->dev, sizeof(*spc), GFP_KERNEL);
	if (!spc)
		return -ENOMEM;

	spc->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(spc->base))
		return PTR_ERR(spc->base);

	spc->dev = &pdev->dev;
	platform_set_drvdata(pdev, spc);

	ret = sprd_pwm_clk_init(spc);
	if (ret)
		return ret;

	spc->chip.dev = &pdev->dev;
	spc->chip.ops = &sprd_pwm_ops;
	spc->chip.base = -1;
	spc->chip.npwm = spc->num_pwms;

	ret = pwmchip_add(&spc->chip);
	if (ret)
		dev_err(&pdev->dev, "failed to add PWM chip\n");

	return ret;
}