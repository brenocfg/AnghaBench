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
struct hibvt_pwm_soc {int num_pwms; } ;
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * ops; } ;
struct hibvt_pwm_chip {int /*<<< orphan*/  base; TYPE_1__ chip; int /*<<< orphan*/  clk; int /*<<< orphan*/  rstc; struct hibvt_pwm_soc const* soc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWM_CTRL_ADDR (int) ; 
 int /*<<< orphan*/  PWM_KEEP_MASK ; 
 int PWM_KEEP_SHIFT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct hibvt_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hibvt_pwm_ops ; 
 int /*<<< orphan*/  hibvt_pwm_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct hibvt_pwm_soc* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hibvt_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hibvt_pwm_probe(struct platform_device *pdev)
{
	const struct hibvt_pwm_soc *soc =
				of_device_get_match_data(&pdev->dev);
	struct hibvt_pwm_chip *pwm_chip;
	struct resource *res;
	int ret;
	int i;

	pwm_chip = devm_kzalloc(&pdev->dev, sizeof(*pwm_chip), GFP_KERNEL);
	if (pwm_chip == NULL)
		return -ENOMEM;

	pwm_chip->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pwm_chip->clk)) {
		dev_err(&pdev->dev, "getting clock failed with %ld\n",
				PTR_ERR(pwm_chip->clk));
		return PTR_ERR(pwm_chip->clk);
	}

	pwm_chip->chip.ops = &hibvt_pwm_ops;
	pwm_chip->chip.dev = &pdev->dev;
	pwm_chip->chip.base = -1;
	pwm_chip->chip.npwm = soc->num_pwms;
	pwm_chip->chip.of_xlate = of_pwm_xlate_with_flags;
	pwm_chip->chip.of_pwm_n_cells = 3;
	pwm_chip->soc = soc;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pwm_chip->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pwm_chip->base))
		return PTR_ERR(pwm_chip->base);

	ret = clk_prepare_enable(pwm_chip->clk);
	if (ret < 0)
		return ret;

	pwm_chip->rstc = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (IS_ERR(pwm_chip->rstc)) {
		clk_disable_unprepare(pwm_chip->clk);
		return PTR_ERR(pwm_chip->rstc);
	}

	reset_control_assert(pwm_chip->rstc);
	msleep(30);
	reset_control_deassert(pwm_chip->rstc);

	ret = pwmchip_add(&pwm_chip->chip);
	if (ret < 0) {
		clk_disable_unprepare(pwm_chip->clk);
		return ret;
	}

	for (i = 0; i < pwm_chip->chip.npwm; i++) {
		hibvt_pwm_set_bits(pwm_chip->base, PWM_CTRL_ADDR(i),
				PWM_KEEP_MASK, (0x1 << PWM_KEEP_SHIFT));
	}

	platform_set_drvdata(pdev, pwm_chip);

	return 0;
}