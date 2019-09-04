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

__attribute__((used)) static void ccu_mp_find_best(unsigned long parent, unsigned long rate,
			     unsigned int max_m, unsigned int max_p,
			     unsigned int *m, unsigned int *p)
{
	unsigned long best_rate = 0;
	unsigned int best_m = 0, best_p = 0;
	unsigned int _m, _p;

	for (_p = 1; _p <= max_p; _p <<= 1) {
		for (_m = 1; _m <= max_m; _m++) {
			unsigned long tmp_rate = parent / _p / _m;

			if (tmp_rate > rate)
				continue;

			if ((rate - tmp_rate) < (rate - best_rate)) {
				best_rate = tmp_rate;
				best_m = _m;
				best_p = _p;
			}
		}
	}

	*m = best_m;
	*p = best_p;
}