#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct resource {int dummy; } ;
struct pwm_device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lpc18xx_pwm_data {int dummy; } ;
struct TYPE_3__ {int base; int npwm; int of_pwm_n_cells; struct pwm_device* pwms; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct lpc18xx_pwm_chip {int max_period_ns; int /*<<< orphan*/  pwm_clk; TYPE_1__ chip; int /*<<< orphan*/ * dev; int /*<<< orphan*/  period_event; int /*<<< orphan*/  event_map; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  min_period_ns; int /*<<< orphan*/  period_lock; int /*<<< orphan*/  res_lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LPC18XX_PWM_BIDIR ; 
 int /*<<< orphan*/  LPC18XX_PWM_CONFIG ; 
 int LPC18XX_PWM_CONFIG_UNIFY ; 
 int /*<<< orphan*/  LPC18XX_PWM_CTRL ; 
 int LPC18XX_PWM_CTRL_HALT ; 
 int /*<<< orphan*/  LPC18XX_PWM_EVCTRL (int /*<<< orphan*/ ) ; 
 int LPC18XX_PWM_EVCTRL_COMB_MATCH ; 
 int LPC18XX_PWM_EVCTRL_MATCH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_PWM_EVENT_PERIOD ; 
 int /*<<< orphan*/  LPC18XX_PWM_EVSTATEMSK (int /*<<< orphan*/ ) ; 
 int LPC18XX_PWM_EVSTATEMSK_ALL ; 
 int /*<<< orphan*/  LPC18XX_PWM_LIMIT ; 
 int LPC18XX_PWM_PRE (int /*<<< orphan*/ ) ; 
 int LPC18XX_PWM_PRE_MASK ; 
 int LPC18XX_PWM_TIMER_MAX ; 
 scalar_t__ NSEC_PER_SEC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_pwm_ops ; 
 int lpc18xx_pwm_readl (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_pwm_writel (struct lpc18xx_pwm_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_pwm_chip*) ; 
 int /*<<< orphan*/  pwm_set_chip_data (struct pwm_device*,struct lpc18xx_pwm_data*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  pwmchip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_pwm_probe(struct platform_device *pdev)
{
	struct lpc18xx_pwm_chip *lpc18xx_pwm;
	struct pwm_device *pwm;
	struct resource *res;
	int ret, i;
	u64 val;

	lpc18xx_pwm = devm_kzalloc(&pdev->dev, sizeof(*lpc18xx_pwm),
				   GFP_KERNEL);
	if (!lpc18xx_pwm)
		return -ENOMEM;

	lpc18xx_pwm->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	lpc18xx_pwm->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(lpc18xx_pwm->base))
		return PTR_ERR(lpc18xx_pwm->base);

	lpc18xx_pwm->pwm_clk = devm_clk_get(&pdev->dev, "pwm");
	if (IS_ERR(lpc18xx_pwm->pwm_clk)) {
		dev_err(&pdev->dev, "failed to get pwm clock\n");
		return PTR_ERR(lpc18xx_pwm->pwm_clk);
	}

	ret = clk_prepare_enable(lpc18xx_pwm->pwm_clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not prepare or enable pwm clock\n");
		return ret;
	}

	lpc18xx_pwm->clk_rate = clk_get_rate(lpc18xx_pwm->pwm_clk);
	if (!lpc18xx_pwm->clk_rate) {
		dev_err(&pdev->dev, "pwm clock has no frequency\n");
		ret = -EINVAL;
		goto disable_pwmclk;
	}

	mutex_init(&lpc18xx_pwm->res_lock);
	mutex_init(&lpc18xx_pwm->period_lock);

	val = (u64)NSEC_PER_SEC * LPC18XX_PWM_TIMER_MAX;
	do_div(val, lpc18xx_pwm->clk_rate);
	lpc18xx_pwm->max_period_ns = val;

	lpc18xx_pwm->min_period_ns = DIV_ROUND_UP(NSEC_PER_SEC,
						  lpc18xx_pwm->clk_rate);

	lpc18xx_pwm->chip.dev = &pdev->dev;
	lpc18xx_pwm->chip.ops = &lpc18xx_pwm_ops;
	lpc18xx_pwm->chip.base = -1;
	lpc18xx_pwm->chip.npwm = 16;
	lpc18xx_pwm->chip.of_xlate = of_pwm_xlate_with_flags;
	lpc18xx_pwm->chip.of_pwm_n_cells = 3;

	/* SCT counter must be in unify (32 bit) mode */
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_CONFIG,
			   LPC18XX_PWM_CONFIG_UNIFY);

	/*
	 * Everytime the timer counter reaches the period value, the related
	 * event will be triggered and the counter reset to 0.
	 */
	set_bit(LPC18XX_PWM_EVENT_PERIOD, &lpc18xx_pwm->event_map);
	lpc18xx_pwm->period_event = LPC18XX_PWM_EVENT_PERIOD;

	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_EVSTATEMSK(lpc18xx_pwm->period_event),
			   LPC18XX_PWM_EVSTATEMSK_ALL);

	val = LPC18XX_PWM_EVCTRL_MATCH(lpc18xx_pwm->period_event) |
	      LPC18XX_PWM_EVCTRL_COMB_MATCH;
	lpc18xx_pwm_writel(lpc18xx_pwm,
			   LPC18XX_PWM_EVCTRL(lpc18xx_pwm->period_event), val);

	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_LIMIT,
			   BIT(lpc18xx_pwm->period_event));

	ret = pwmchip_add(&lpc18xx_pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add failed: %d\n", ret);
		goto disable_pwmclk;
	}

	for (i = 0; i < lpc18xx_pwm->chip.npwm; i++) {
		struct lpc18xx_pwm_data *data;

		pwm = &lpc18xx_pwm->chip.pwms[i];

		data = devm_kzalloc(lpc18xx_pwm->dev, sizeof(*data),
				    GFP_KERNEL);
		if (!data) {
			ret = -ENOMEM;
			goto remove_pwmchip;
		}

		pwm_set_chip_data(pwm, data);
	}

	platform_set_drvdata(pdev, lpc18xx_pwm);

	val = lpc18xx_pwm_readl(lpc18xx_pwm, LPC18XX_PWM_CTRL);
	val &= ~LPC18XX_PWM_BIDIR;
	val &= ~LPC18XX_PWM_CTRL_HALT;
	val &= ~LPC18XX_PWM_PRE_MASK;
	val |= LPC18XX_PWM_PRE(0);
	lpc18xx_pwm_writel(lpc18xx_pwm, LPC18XX_PWM_CTRL, val);

	return 0;

remove_pwmchip:
	pwmchip_remove(&lpc18xx_pwm->chip);
disable_pwmclk:
	clk_disable_unprepare(lpc18xx_pwm->pwm_clk);
	return ret;
}