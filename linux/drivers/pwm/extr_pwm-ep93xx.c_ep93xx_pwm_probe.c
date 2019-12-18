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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; int npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct ep93xx_pwm {TYPE_1__ chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ep93xx_pwm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep93xx_pwm_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ep93xx_pwm*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int ep93xx_pwm_probe(struct platform_device *pdev)
{
	struct ep93xx_pwm *ep93xx_pwm;
	struct resource *res;
	int ret;

	ep93xx_pwm = devm_kzalloc(&pdev->dev, sizeof(*ep93xx_pwm), GFP_KERNEL);
	if (!ep93xx_pwm)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ep93xx_pwm->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ep93xx_pwm->base))
		return PTR_ERR(ep93xx_pwm->base);

	ep93xx_pwm->clk = devm_clk_get(&pdev->dev, "pwm_clk");
	if (IS_ERR(ep93xx_pwm->clk))
		return PTR_ERR(ep93xx_pwm->clk);

	ep93xx_pwm->chip.dev = &pdev->dev;
	ep93xx_pwm->chip.ops = &ep93xx_pwm_ops;
	ep93xx_pwm->chip.base = -1;
	ep93xx_pwm->chip.npwm = 1;

	ret = pwmchip_add(&ep93xx_pwm->chip);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, ep93xx_pwm);
	return 0;
}