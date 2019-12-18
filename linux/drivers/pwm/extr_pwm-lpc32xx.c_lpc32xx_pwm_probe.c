#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int npwm; int base; TYPE_1__* pwms; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct lpc32xx_pwm_chip {TYPE_2__ chip; scalar_t__ base; scalar_t__ clk; } ;
struct TYPE_3__ {int hwpwm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  PWM_PIN_LEVEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct lpc32xx_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_pwm_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc32xx_pwm_chip*) ; 
 int pwmchip_add (TYPE_2__*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc32xx_pwm_probe(struct platform_device *pdev)
{
	struct lpc32xx_pwm_chip *lpc32xx;
	struct resource *res;
	int ret;
	u32 val;

	lpc32xx = devm_kzalloc(&pdev->dev, sizeof(*lpc32xx), GFP_KERNEL);
	if (!lpc32xx)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	lpc32xx->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(lpc32xx->base))
		return PTR_ERR(lpc32xx->base);

	lpc32xx->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(lpc32xx->clk))
		return PTR_ERR(lpc32xx->clk);

	lpc32xx->chip.dev = &pdev->dev;
	lpc32xx->chip.ops = &lpc32xx_pwm_ops;
	lpc32xx->chip.npwm = 1;
	lpc32xx->chip.base = -1;

	ret = pwmchip_add(&lpc32xx->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add PWM chip, error %d\n", ret);
		return ret;
	}

	/* When PWM is disable, configure the output to the default value */
	val = readl(lpc32xx->base + (lpc32xx->chip.pwms[0].hwpwm << 2));
	val &= ~PWM_PIN_LEVEL;
	writel(val, lpc32xx->base + (lpc32xx->chip.pwms[0].hwpwm << 2));

	platform_set_drvdata(pdev, lpc32xx);

	return 0;
}