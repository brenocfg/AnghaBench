#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fsl_pwm_periodcfg {int dummy; } ;
struct fsl_pwm_chip {int /*<<< orphan*/ * clk; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 size_t FSL_PWM_CLK_EXT ; 
 size_t FSL_PWM_CLK_FIX ; 
 int FSL_PWM_CLK_SYS ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int fsl_pwm_calculate_period_clk (struct fsl_pwm_chip*,unsigned int,int,struct fsl_pwm_periodcfg*) ; 

__attribute__((used)) static bool fsl_pwm_calculate_period(struct fsl_pwm_chip *fpc,
				     unsigned int period_ns,
				     struct fsl_pwm_periodcfg *periodcfg)
{
	enum fsl_pwm_clk m0, m1;
	unsigned long fix_rate, ext_rate;
	bool ret;

	ret = fsl_pwm_calculate_period_clk(fpc, period_ns, FSL_PWM_CLK_SYS,
					   periodcfg);
	if (ret)
		return true;

	fix_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_FIX]);
	ext_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_EXT]);

	if (fix_rate > ext_rate) {
		m0 = FSL_PWM_CLK_FIX;
		m1 = FSL_PWM_CLK_EXT;
	} else {
		m0 = FSL_PWM_CLK_EXT;
		m1 = FSL_PWM_CLK_FIX;
	}

	ret = fsl_pwm_calculate_period_clk(fpc, period_ns, m0, periodcfg);
	if (ret)
		return true;

	return fsl_pwm_calculate_period_clk(fpc, period_ns, m1, periodcfg);
}