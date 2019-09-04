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
struct _ccu_nkmp {unsigned long min_k; unsigned long max_k; unsigned long min_n; unsigned long max_n; unsigned long min_m; unsigned long max_m; unsigned long min_p; unsigned long max_p; unsigned long n; unsigned long k; unsigned long m; unsigned long p; } ;

/* Variables and functions */
 unsigned long ccu_nkmp_calc_rate (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void ccu_nkmp_find_best(unsigned long parent, unsigned long rate,
			       struct _ccu_nkmp *nkmp)
{
	unsigned long best_rate = 0;
	unsigned long best_n = 0, best_k = 0, best_m = 0, best_p = 0;
	unsigned long _n, _k, _m, _p;

	for (_k = nkmp->min_k; _k <= nkmp->max_k; _k++) {
		for (_n = nkmp->min_n; _n <= nkmp->max_n; _n++) {
			for (_m = nkmp->min_m; _m <= nkmp->max_m; _m++) {
				for (_p = nkmp->min_p; _p <= nkmp->max_p; _p <<= 1) {
					unsigned long tmp_rate;

					tmp_rate = ccu_nkmp_calc_rate(parent,
								      _n, _k,
								      _m, _p);

					if (tmp_rate > rate)
						continue;

					if ((rate - tmp_rate) < (rate - best_rate)) {
						best_rate = tmp_rate;
						best_n = _n;
						best_k = _k;
						best_m = _m;
						best_p = _p;
					}
				}
			}
		}
	}

	nkmp->n = best_n;
	nkmp->k = best_k;
	nkmp->m = best_m;
	nkmp->p = best_p;
}