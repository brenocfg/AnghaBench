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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static unsigned long sun4i_tmds_calc_divider(unsigned long rate,
					     unsigned long parent_rate,
					     u8 div_offset,
					     u8 *div,
					     bool *half)
{
	unsigned long best_rate = 0;
	u8 best_m = 0, m;
	bool is_double;

	for (m = div_offset ?: 1; m < (16 + div_offset); m++) {
		u8 d;

		for (d = 1; d < 3; d++) {
			unsigned long tmp_rate;

			tmp_rate = parent_rate / m / d;

			if (tmp_rate > rate)
				continue;

			if (!best_rate ||
			    (rate - tmp_rate) < (rate - best_rate)) {
				best_rate = tmp_rate;
				best_m = m;
				is_double = d;
			}
		}
	}

	if (div && half) {
		*div = best_m;
		*half = is_double;
	}

	return best_rate;
}