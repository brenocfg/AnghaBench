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
typedef  int u64 ;
typedef  int u32 ;
struct pic32_sys_pll {unsigned long idiv; } ;

/* Variables and functions */
 int PLL_MULT_MAX ; 
 int PLL_ODIV_MAX ; 
 int PLL_ODIV_MIN ; 
 unsigned int abs (unsigned long) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long,int,int,unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static unsigned long spll_calc_mult_div(struct pic32_sys_pll *pll,
					unsigned long rate,
					unsigned long parent_rate,
					u32 *mult_p, u32 *odiv_p)
{
	u32 mul, div, best_mul = 1, best_div = 1;
	unsigned long new_rate, best_rate = rate;
	unsigned int best_delta = -1, delta, match_found = 0;
	u64 rate64;

	parent_rate /= pll->idiv;

	for (mul = 1; mul <= PLL_MULT_MAX; mul++) {
		for (div = PLL_ODIV_MIN; div <= PLL_ODIV_MAX; div++) {
			rate64 = parent_rate;
			rate64 *= mul;
			do_div(rate64, 1 << div);
			new_rate = rate64;
			delta = abs(rate - new_rate);
			if ((new_rate >= rate) && (delta < best_delta)) {
				best_delta = delta;
				best_rate = new_rate;
				best_mul = mul;
				best_div = div;
				match_found = 1;
			}
		}
	}

	if (!match_found) {
		pr_warn("spll: no match found\n");
		return 0;
	}

	pr_debug("rate %lu, par_rate %lu/mult %u, div %u, best_rate %lu\n",
		 rate, parent_rate, best_mul, best_div, best_rate);

	if (mult_p)
		*mult_p = best_mul - 1;

	if (odiv_p)
		*odiv_p = best_div;

	return best_rate;
}