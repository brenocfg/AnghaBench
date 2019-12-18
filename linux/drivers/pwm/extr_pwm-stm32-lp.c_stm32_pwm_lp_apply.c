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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct stm32_pwm_lp {int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; TYPE_1__ chip; } ;
struct pwm_state {unsigned long long period; unsigned long long duty_cycle; int polarity; scalar_t__ enabled; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIELD_GET (int,int) ; 
 int FIELD_PREP (int,int) ; 
 unsigned long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  STM32_LPTIM_ARR ; 
 int /*<<< orphan*/  STM32_LPTIM_CFGR ; 
 int /*<<< orphan*/  STM32_LPTIM_CMP ; 
 unsigned long long STM32_LPTIM_CMPOKCF_ARROKCF ; 
 int STM32_LPTIM_CMPOK_ARROK ; 
 int STM32_LPTIM_CNTSTRT ; 
 int /*<<< orphan*/  STM32_LPTIM_CR ; 
 unsigned long long STM32_LPTIM_ENABLE ; 
 int /*<<< orphan*/  STM32_LPTIM_ICR ; 
 int /*<<< orphan*/  STM32_LPTIM_ISR ; 
 unsigned long long STM32_LPTIM_MAX_ARR ; 
 int STM32_LPTIM_MAX_PRESCALER ; 
 int STM32_LPTIM_PRESC ; 
 int STM32_LPTIM_WAVPOL ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  pwm_get_state (struct pwm_device*,struct pwm_state*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 struct stm32_pwm_lp* to_stm32_pwm_lp (struct pwm_chip*) ; 

__attribute__((used)) static int stm32_pwm_lp_apply(struct pwm_chip *chip, struct pwm_device *pwm,
			      const struct pwm_state *state)
{
	struct stm32_pwm_lp *priv = to_stm32_pwm_lp(chip);
	unsigned long long prd, div, dty;
	struct pwm_state cstate;
	u32 val, mask, cfgr, presc = 0;
	bool reenable;
	int ret;

	pwm_get_state(pwm, &cstate);
	reenable = !cstate.enabled;

	if (!state->enabled) {
		if (cstate.enabled) {
			/* Disable LP timer */
			ret = regmap_write(priv->regmap, STM32_LPTIM_CR, 0);
			if (ret)
				return ret;
			/* disable clock to PWM counter */
			clk_disable(priv->clk);
		}
		return 0;
	}

	/* Calculate the period and prescaler value */
	div = (unsigned long long)clk_get_rate(priv->clk) * state->period;
	do_div(div, NSEC_PER_SEC);
	if (!div) {
		/* Clock is too slow to achieve requested period. */
		dev_dbg(priv->chip.dev, "Can't reach %u ns\n",	state->period);
		return -EINVAL;
	}

	prd = div;
	while (div > STM32_LPTIM_MAX_ARR) {
		presc++;
		if ((1 << presc) > STM32_LPTIM_MAX_PRESCALER) {
			dev_err(priv->chip.dev, "max prescaler exceeded\n");
			return -EINVAL;
		}
		div = prd >> presc;
	}
	prd = div;

	/* Calculate the duty cycle */
	dty = prd * state->duty_cycle;
	do_div(dty, state->period);

	if (!cstate.enabled) {
		/* enable clock to drive PWM counter */
		ret = clk_enable(priv->clk);
		if (ret)
			return ret;
	}

	ret = regmap_read(priv->regmap, STM32_LPTIM_CFGR, &cfgr);
	if (ret)
		goto err;

	if ((FIELD_GET(STM32_LPTIM_PRESC, cfgr) != presc) ||
	    (FIELD_GET(STM32_LPTIM_WAVPOL, cfgr) != state->polarity)) {
		val = FIELD_PREP(STM32_LPTIM_PRESC, presc);
		val |= FIELD_PREP(STM32_LPTIM_WAVPOL, state->polarity);
		mask = STM32_LPTIM_PRESC | STM32_LPTIM_WAVPOL;

		/* Must disable LP timer to modify CFGR */
		reenable = true;
		ret = regmap_write(priv->regmap, STM32_LPTIM_CR, 0);
		if (ret)
			goto err;

		ret = regmap_update_bits(priv->regmap, STM32_LPTIM_CFGR, mask,
					 val);
		if (ret)
			goto err;
	}

	if (reenable) {
		/* Must (re)enable LP timer to modify CMP & ARR */
		ret = regmap_write(priv->regmap, STM32_LPTIM_CR,
				   STM32_LPTIM_ENABLE);
		if (ret)
			goto err;
	}

	ret = regmap_write(priv->regmap, STM32_LPTIM_ARR, prd - 1);
	if (ret)
		goto err;

	ret = regmap_write(priv->regmap, STM32_LPTIM_CMP, prd - (1 + dty));
	if (ret)
		goto err;

	/* ensure CMP & ARR registers are properly written */
	ret = regmap_read_poll_timeout(priv->regmap, STM32_LPTIM_ISR, val,
				       (val & STM32_LPTIM_CMPOK_ARROK),
				       100, 1000);
	if (ret) {
		dev_err(priv->chip.dev, "ARR/CMP registers write issue\n");
		goto err;
	}
	ret = regmap_write(priv->regmap, STM32_LPTIM_ICR,
			   STM32_LPTIM_CMPOKCF_ARROKCF);
	if (ret)
		goto err;

	if (reenable) {
		/* Start LP timer in continuous mode */
		ret = regmap_update_bits(priv->regmap, STM32_LPTIM_CR,
					 STM32_LPTIM_CNTSTRT,
					 STM32_LPTIM_CNTSTRT);
		if (ret) {
			regmap_write(priv->regmap, STM32_LPTIM_CR, 0);
			goto err;
		}
	}

	return 0;
err:
	if (!cstate.enabled)
		clk_disable(priv->clk);

	return ret;
}