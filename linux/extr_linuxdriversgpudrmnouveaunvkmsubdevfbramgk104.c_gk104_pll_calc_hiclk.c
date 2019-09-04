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
typedef  int u16 ;

/* Variables and functions */
 int gk104_calc_pll_output (int,int,int,int,int) ; 

__attribute__((used)) static int
gk104_pll_calc_hiclk(int target_khz, int crystal,
		int *N1, int *fN1, int *M1, int *P1,
		int *N2, int *M2, int *P2)
{
	int best_err = target_khz, p_ref, n_ref;
	bool upper = false;

	*M1 = 1;
	/* M has to be 1, otherwise it gets unstable */
	*M2 = 1;
	/* can be 1 or 2, sticking with 1 for simplicity */
	*P2 = 1;

	for (p_ref = 0x7; p_ref >= 0x5; --p_ref) {
		for (n_ref = 0x25; n_ref <= 0x2b; ++n_ref) {
			int cur_N, cur_clk, cur_err;

			cur_clk = gk104_calc_pll_output(0, 1, n_ref, p_ref, crystal);
			cur_N = target_khz / cur_clk;
			cur_err = target_khz
				- gk104_calc_pll_output(0xf000, 1, cur_N, 1, cur_clk);

			/* we found a better combination */
			if (cur_err < best_err) {
				best_err = cur_err;
				*N2 = cur_N;
				*N1 = n_ref;
				*P1 = p_ref;
				upper = false;
			}

			cur_N += 1;
			cur_err = gk104_calc_pll_output(0xf000, 1, cur_N, 1, cur_clk)
				- target_khz;
			if (cur_err < best_err) {
				best_err = cur_err;
				*N2 = cur_N;
				*N1 = n_ref;
				*P1 = p_ref;
				upper = true;
			}
		}
	}

	/* adjust fN to get closer to the target clock */
	*fN1 = (u16)((((best_err / *N2 * *P2) * (*P1 * *M1)) << 13) / crystal);
	if (upper)
		*fN1 = (u16)(1 - *fN1);

	return gk104_calc_pll_output(*fN1, 1, *N1, *P1, crystal);
}