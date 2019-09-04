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

/* Variables and functions */

__attribute__((used)) static unsigned radeon_uvd_calc_upll_post_div(unsigned vco_freq,
					      unsigned target_freq,
					      unsigned pd_min,
					      unsigned pd_even)
{
	unsigned post_div = vco_freq / target_freq;

	/* adjust to post divider minimum value */
	if (post_div < pd_min)
		post_div = pd_min;

	/* we alway need a frequency less than or equal the target */
	if ((vco_freq / post_div) > target_freq)
		post_div += 1;

	/* post dividers above a certain value must be even */
	if (post_div > pd_even && post_div % 2)
		post_div += 1;

	return post_div;
}