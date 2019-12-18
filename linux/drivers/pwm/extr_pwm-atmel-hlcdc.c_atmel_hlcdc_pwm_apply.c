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
typedef  int u64 ;
typedef  int u32 ;
struct pwm_state {int duty_cycle; int period; scalar_t__ polarity; scalar_t__ enabled; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct clk {int dummy; } ;
struct atmel_hlcdc_pwm {struct clk* cur_clk; TYPE_1__* errata; struct atmel_hlcdc* hlcdc; } ;
struct atmel_hlcdc {int /*<<< orphan*/  regmap; struct clk* sys_clk; struct clk* slow_clk; } ;
struct TYPE_2__ {scalar_t__ div1_clk_erratum; scalar_t__ slow_clk_erratum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_CFG (int) ; 
 int ATMEL_HLCDC_CLKPWMSEL ; 
 int /*<<< orphan*/  ATMEL_HLCDC_DIS ; 
 int /*<<< orphan*/  ATMEL_HLCDC_EN ; 
 unsigned int ATMEL_HLCDC_PWM ; 
 int ATMEL_HLCDC_PWMCVAL (int) ; 
 int ATMEL_HLCDC_PWMCVAL_MASK ; 
 int ATMEL_HLCDC_PWMPOL ; 
 int ATMEL_HLCDC_PWMPS (int) ; 
 int ATMEL_HLCDC_PWMPS_MASK ; 
 int ATMEL_HLCDC_PWMPS_MAX ; 
 int /*<<< orphan*/  ATMEL_HLCDC_SR ; 
 int EINVAL ; 
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ PWM_POLARITY_NORMAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct atmel_hlcdc_pwm* to_atmel_hlcdc_pwm (struct pwm_chip*) ; 

__attribute__((used)) static int atmel_hlcdc_pwm_apply(struct pwm_chip *c, struct pwm_device *pwm,
				 const struct pwm_state *state)
{
	struct atmel_hlcdc_pwm *chip = to_atmel_hlcdc_pwm(c);
	struct atmel_hlcdc *hlcdc = chip->hlcdc;
	unsigned int status;
	int ret;

	if (state->enabled) {
		struct clk *new_clk = hlcdc->slow_clk;
		u64 pwmcval = state->duty_cycle * 256;
		unsigned long clk_freq;
		u64 clk_period_ns;
		u32 pwmcfg;
		int pres;

		if (!chip->errata || !chip->errata->slow_clk_erratum) {
			clk_freq = clk_get_rate(new_clk);
			if (!clk_freq)
				return -EINVAL;

			clk_period_ns = (u64)NSEC_PER_SEC * 256;
			do_div(clk_period_ns, clk_freq);
		}

		/* Errata: cannot use slow clk on some IP revisions */
		if ((chip->errata && chip->errata->slow_clk_erratum) ||
		    clk_period_ns > state->period) {
			new_clk = hlcdc->sys_clk;
			clk_freq = clk_get_rate(new_clk);
			if (!clk_freq)
				return -EINVAL;

			clk_period_ns = (u64)NSEC_PER_SEC * 256;
			do_div(clk_period_ns, clk_freq);
		}

		for (pres = 0; pres <= ATMEL_HLCDC_PWMPS_MAX; pres++) {
		/* Errata: cannot divide by 1 on some IP revisions */
			if (!pres && chip->errata &&
			    chip->errata->div1_clk_erratum)
				continue;

			if ((clk_period_ns << pres) >= state->period)
				break;
		}

		if (pres > ATMEL_HLCDC_PWMPS_MAX)
			return -EINVAL;

		pwmcfg = ATMEL_HLCDC_PWMPS(pres);

		if (new_clk != chip->cur_clk) {
			u32 gencfg = 0;
			int ret;

			ret = clk_prepare_enable(new_clk);
			if (ret)
				return ret;

			clk_disable_unprepare(chip->cur_clk);
			chip->cur_clk = new_clk;

			if (new_clk == hlcdc->sys_clk)
				gencfg = ATMEL_HLCDC_CLKPWMSEL;

			ret = regmap_update_bits(hlcdc->regmap,
						 ATMEL_HLCDC_CFG(0),
						 ATMEL_HLCDC_CLKPWMSEL,
						 gencfg);
			if (ret)
				return ret;
		}

		do_div(pwmcval, state->period);

		/*
		 * The PWM duty cycle is configurable from 0/256 to 255/256 of
		 * the period cycle. Hence we can't set a duty cycle occupying
		 * the whole period cycle if we're asked to.
		 * Set it to 255 if pwmcval is greater than 256.
		 */
		if (pwmcval > 255)
			pwmcval = 255;

		pwmcfg |= ATMEL_HLCDC_PWMCVAL(pwmcval);

		if (state->polarity == PWM_POLARITY_NORMAL)
			pwmcfg |= ATMEL_HLCDC_PWMPOL;

		ret = regmap_update_bits(hlcdc->regmap, ATMEL_HLCDC_CFG(6),
					 ATMEL_HLCDC_PWMCVAL_MASK |
					 ATMEL_HLCDC_PWMPS_MASK |
					 ATMEL_HLCDC_PWMPOL,
					 pwmcfg);
		if (ret)
			return ret;

		ret = regmap_write(hlcdc->regmap, ATMEL_HLCDC_EN,
				   ATMEL_HLCDC_PWM);
		if (ret)
			return ret;

		ret = regmap_read_poll_timeout(hlcdc->regmap, ATMEL_HLCDC_SR,
					       status,
					       status & ATMEL_HLCDC_PWM,
					       10, 0);
		if (ret)
			return ret;
	} else {
		ret = regmap_write(hlcdc->regmap, ATMEL_HLCDC_DIS,
				   ATMEL_HLCDC_PWM);
		if (ret)
			return ret;

		ret = regmap_read_poll_timeout(hlcdc->regmap, ATMEL_HLCDC_SR,
					       status,
					       !(status & ATMEL_HLCDC_PWM),
					       10, 0);
		if (ret)
			return ret;

		clk_disable_unprepare(chip->cur_clk);
		chip->cur_clk = NULL;
	}

	return 0;
}