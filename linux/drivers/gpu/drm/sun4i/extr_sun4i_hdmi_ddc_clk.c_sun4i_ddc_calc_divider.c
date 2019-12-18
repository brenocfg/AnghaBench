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
 scalar_t__ abs (unsigned long) ; 

__attribute__((used)) static unsigned long sun4i_ddc_calc_divider(unsigned long rate,
					    unsigned long parent_rate,
					    const u8 pre_div,
					    const u8 m_offset,
					    u8 *m, u8 *n)
{
	unsigned long best_rate = 0;
	u8 best_m = 0, best_n = 0, _m, _n;

	for (_m = 0; _m < 8; _m++) {
		for (_n = 0; _n < 8; _n++) {
			unsigned long tmp_rate;

			tmp_rate = (((parent_rate / pre_div) / 10) >> _n) /
				(_m + m_offset);

			if (tmp_rate > rate)
				continue;

			if (abs(rate - tmp_rate) < abs(rate - best_rate)) {
				best_rate = tmp_rate;
				best_m = _m;
				best_n = _n;
			}
		}
	}

	if (m && n) {
		*m = best_m;
		*n = best_n;
	}

	return best_rate;
}