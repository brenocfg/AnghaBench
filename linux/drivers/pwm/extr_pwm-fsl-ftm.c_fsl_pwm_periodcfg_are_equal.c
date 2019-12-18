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
struct fsl_pwm_periodcfg {scalar_t__ clk_select; scalar_t__ clk_ps; scalar_t__ mod_period; } ;

/* Variables and functions */

__attribute__((used)) static bool fsl_pwm_periodcfg_are_equal(const struct fsl_pwm_periodcfg *a,
					const struct fsl_pwm_periodcfg *b)
{
	if (a->clk_select != b->clk_select)
		return false;
	if (a->clk_ps != b->clk_ps)
		return false;
	if (a->mod_period != b->mod_period)
		return false;
	return true;
}