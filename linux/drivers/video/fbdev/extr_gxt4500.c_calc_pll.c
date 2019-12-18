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
struct gxt4500_par {int refclk_ps; int pll_m; int pll_n; int pll_pd1; int pll_pd2; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 

__attribute__((used)) static int calc_pll(int period_ps, struct gxt4500_par *par)
{
	int m, n, pdiv1, pdiv2, postdiv;
	int pll_period, best_error, t, intf;

	/* only deal with range 5MHz - 300MHz */
	if (period_ps < 3333 || period_ps > 200000)
		return -1;

	best_error = 1000000;
	for (pdiv1 = 1; pdiv1 <= 8; ++pdiv1) {
		for (pdiv2 = 1; pdiv2 <= pdiv1; ++pdiv2) {
			postdiv = pdiv1 * pdiv2;
			pll_period = DIV_ROUND_UP(period_ps, postdiv);
			/* keep pll in range 350..600 MHz */
			if (pll_period < 1666 || pll_period > 2857)
				continue;
			for (m = 1; m <= 64; ++m) {
				intf = m * par->refclk_ps;
				if (intf > 500000)
					break;
				n = intf * postdiv / period_ps;
				if (n < 3 || n > 160)
					continue;
				t = par->refclk_ps * m * postdiv / n;
				t -= period_ps;
				if (t >= 0 && t < best_error) {
					par->pll_m = m;
					par->pll_n = n;
					par->pll_pd1 = pdiv1;
					par->pll_pd2 = pdiv2;
					best_error = t;
				}
			}
		}
	}
	if (best_error == 1000000)
		return -1;
	return 0;
}