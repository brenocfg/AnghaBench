#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct resource {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {TYPE_1__* data; } ;
struct TYPE_17__ {int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; TYPE_3__* dev; } ;
struct img_pwm_chip {int max_period_ns; int min_period_ns; TYPE_2__ chip; TYPE_1__* data; void* pwm_clk; void* sys_clk; void* periph_regs; void* base; TYPE_3__* dev; } ;
struct TYPE_16__ {int max_timebase; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMG_PWM_NPWM ; 
 int /*<<< orphan*/  IMG_PWM_PM_TIMEOUT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int MIN_TMBASE_STEPS ; 
 scalar_t__ NSEC_PER_SEC ; 
 int PTR_ERR (void*) ; 
 unsigned long clk_get_rate (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct img_pwm_chip* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 int /*<<< orphan*/  img_pwm_of_match ; 
 int /*<<< orphan*/  img_pwm_ops ; 
 int img_pwm_runtime_resume (TYPE_3__*) ; 
 int /*<<< orphan*/  img_pwm_runtime_suspend (TYPE_3__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct img_pwm_chip*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (TYPE_3__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_3__*) ; 
 int pwmchip_add (TYPE_2__*) ; 
 void* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int img_pwm_probe(struct platform_device *pdev)
{
	int ret;
	u64 val;
	unsigned long clk_rate;
	struct resource *res;
	struct img_pwm_chip *pwm;
	const struct of_device_id *of_dev_id;

	pwm = devm_kzalloc(&pdev->dev, sizeof(*pwm), GFP_KERNEL);
	if (!pwm)
		return -ENOMEM;

	pwm->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pwm->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pwm->base))
		return PTR_ERR(pwm->base);

	of_dev_id = of_match_device(img_pwm_of_match, &pdev->dev);
	if (!of_dev_id)
		return -ENODEV;
	pwm->data = of_dev_id->data;

	pwm->periph_regs = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							   "img,cr-periph");
	if (IS_ERR(pwm->periph_regs))
		return PTR_ERR(pwm->periph_regs);

	pwm->sys_clk = devm_clk_get(&pdev->dev, "sys");
	if (IS_ERR(pwm->sys_clk)) {
		dev_err(&pdev->dev, "failed to get system clock\n");
		return PTR_ERR(pwm->sys_clk);
	}

	pwm->pwm_clk = devm_clk_get(&pdev->dev, "pwm");
	if (IS_ERR(pwm->pwm_clk)) {
		dev_err(&pdev->dev, "failed to get pwm clock\n");
		return PTR_ERR(pwm->pwm_clk);
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, IMG_PWM_PM_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);
	if (!pm_runtime_enabled(&pdev->dev)) {
		ret = img_pwm_runtime_resume(&pdev->dev);
		if (ret)
			goto err_pm_disable;
	}

	clk_rate = clk_get_rate(pwm->pwm_clk);
	if (!clk_rate) {
		dev_err(&pdev->dev, "pwm clock has no frequency\n");
		ret = -EINVAL;
		goto err_suspend;
	}

	/* The maximum input clock divider is 512 */
	val = (u64)NSEC_PER_SEC * 512 * pwm->data->max_timebase;
	do_div(val, clk_rate);
	pwm->max_period_ns = val;

	val = (u64)NSEC_PER_SEC * MIN_TMBASE_STEPS;
	do_div(val, clk_rate);
	pwm->min_period_ns = val;

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &img_pwm_ops;
	pwm->chip.base = -1;
	pwm->chip.npwm = IMG_PWM_NPWM;

	ret = pwmchip_add(&pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add failed: %d\n", ret);
		goto err_suspend;
	}

	platform_set_drvdata(pdev, pwm);
	return 0;

err_suspend:
	if (!pm_runtime_enabled(&pdev->dev))
		img_pwm_runtime_suspend(&pdev->dev);
err_pm_disable:
	pm_runtime_disable(&pdev->dev);
	pm_runtime_dont_use_autosuspend(&pdev->dev);
	return ret;
}