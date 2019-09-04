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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int FAPLL_MAIN_MAX_MULT_N ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int ti_fapll_set_div_mult(unsigned long rate,
				 unsigned long parent_rate,
				 u32 *pre_div_p, u32 *mult_n)
{
	/*
	 * So far no luck getting decent clock with PLL divider,
	 * PLL does not seem to lock and the signal does not look
	 * right. It seems the divider can only be used together
	 * with the multiplier?
	 */
	if (rate < parent_rate) {
		pr_warn("FAPLL main divider rates unsupported\n");
		return -EINVAL;
	}

	*mult_n = rate / parent_rate;
	if (*mult_n > FAPLL_MAIN_MAX_MULT_N)
		return -EINVAL;
	*pre_div_p = 1;

	return 0;
}