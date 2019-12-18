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
struct sti_pwm_compat_data {int max_pwm_cnt; unsigned int max_prescale; } ;
struct sti_pwm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  pwm_clk; struct sti_pwm_compat_data* cdata; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long NSEC_PER_SEC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sti_pwm_get_prescale(struct sti_pwm_chip *pc, unsigned long period,
				unsigned int *prescale)
{
	struct sti_pwm_compat_data *cdata = pc->cdata;
	unsigned long clk_rate;
	unsigned long value;
	unsigned int ps;

	clk_rate = clk_get_rate(pc->pwm_clk);
	if (!clk_rate) {
		dev_err(pc->dev, "failed to get clock rate\n");
		return -EINVAL;
	}

	/*
	 * prescale = ((period_ns * clk_rate) / (10^9 * (max_pwm_cnt + 1)) - 1
	 */
	value = NSEC_PER_SEC / clk_rate;
	value *= cdata->max_pwm_cnt + 1;

	if (period % value)
		return -EINVAL;

	ps  = period / value - 1;
	if (ps > cdata->max_prescale)
		return -EINVAL;

	*prescale = ps;

	return 0;
}