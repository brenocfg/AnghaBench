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
struct TYPE_2__ {int base; int npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct puv3_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct puv3_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct puv3_pwm_chip*) ; 
 int /*<<< orphan*/  puv3_pwm_ops ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int pwm_probe(struct platform_device *pdev)
{
	struct puv3_pwm_chip *puv3;
	struct resource *r;
	int ret;

	puv3 = devm_kzalloc(&pdev->dev, sizeof(*puv3), GFP_KERNEL);
	if (!puv3)
		return -ENOMEM;

	puv3->clk = devm_clk_get(&pdev->dev, "OST_CLK");
	if (IS_ERR(puv3->clk))
		return PTR_ERR(puv3->clk);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	puv3->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(puv3->base))
		return PTR_ERR(puv3->base);

	puv3->chip.dev = &pdev->dev;
	puv3->chip.ops = &puv3_pwm_ops;
	puv3->chip.base = -1;
	puv3->chip.npwm = 1;

	ret = pwmchip_add(&puv3->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, puv3);
	return 0;
}