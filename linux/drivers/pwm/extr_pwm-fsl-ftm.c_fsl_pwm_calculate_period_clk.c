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
struct fsl_pwm_periodcfg {int clk_select; unsigned int clk_ps; unsigned long long mod_period; } ;
struct fsl_pwm_chip {int /*<<< orphan*/ * clk; } ;
typedef  enum fsl_pwm_clk { ____Placeholder_fsl_pwm_clk } fsl_pwm_clk ;

/* Variables and functions */
 unsigned long long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 

__attribute__((used)) static bool fsl_pwm_calculate_period_clk(struct fsl_pwm_chip *fpc,
					 unsigned int period_ns,
					 enum fsl_pwm_clk index,
					 struct fsl_pwm_periodcfg *periodcfg
					 )
{
	unsigned long long c;
	unsigned int ps;

	c = clk_get_rate(fpc->clk[index]);
	c = c * period_ns;
	do_div(c, 1000000000UL);

	if (c == 0)
		return false;

	for (ps = 0; ps < 8 ; ++ps, c >>= 1) {
		if (c <= 0x10000) {
			periodcfg->clk_select = index;
			periodcfg->clk_ps = ps;
			periodcfg->mod_period = c - 1;
			return true;
		}
	}
	return false;
}