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
struct _ccu_nk {unsigned int min_k; unsigned int max_k; unsigned int min_n; unsigned int max_n; unsigned int k; unsigned int n; } ;

/* Variables and functions */

__attribute__((used)) static void ccu_nk_find_best(unsigned long parent, unsigned long rate,
			     struct _ccu_nk *nk)
{
	unsigned long best_rate = 0;
	unsigned int best_k = 0, best_n = 0;
	unsigned int _k, _n;

	for (_k = nk->min_k; _k <= nk->max_k; _k++) {
		for (_n = nk->min_n; _n <= nk->max_n; _n++) {
			unsigned long tmp_rate = parent * _n * _k;

			if (tmp_rate > rate)
				continue;

			if ((rate - tmp_rate) < (rate - best_rate)) {
				best_rate = tmp_rate;
				best_k = _k;
				best_n = _n;
			}
		}
	}

	nk->k = best_k;
	nk->n = best_n;
}