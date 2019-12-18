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
struct pll_value {int inputFreq; scalar_t__ clockType; int M; int N; int POD; int OD; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MXCLK_PLL ; 
 scalar_t__ SM750LE ; 
 unsigned int abs (unsigned int) ; 
 scalar_t__ sm750_get_chip_type () ; 

unsigned int sm750_calc_pll_value(unsigned int request_orig,
				  struct pll_value *pll)
{
	/*
	 * as sm750 register definition,
	 * N located in 2,15 and M located in 1,255
	 */
	int N, M, X, d;
	int mini_diff;
	unsigned int RN, quo, rem, fl_quo;
	unsigned int input, request;
	unsigned int tmp_clock, ret;
	const int max_OD = 3;
	int max_d = 6;

	if (sm750_get_chip_type() == SM750LE) {
		/*
		 * SM750LE don't have
		 * programmable PLL and M/N values to work on.
		 * Just return the requested clock.
		 */
		return request_orig;
	}

	ret = 0;
	mini_diff = ~0;
	request = request_orig / 1000;
	input = pll->inputFreq / 1000;

	/*
	 * for MXCLK register,
	 * no POD provided, so need be treated differently
	 */
	if (pll->clockType == MXCLK_PLL)
		max_d = 3;

	for (N = 15; N > 1; N--) {
		/*
		 * RN will not exceed maximum long
		 * if @request <= 285 MHZ (for 32bit cpu)
		 */
		RN = N * request;
		quo = RN / input;
		rem = RN % input;/* rem always small than 14318181 */
		fl_quo = rem * 10000 / input;

		for (d = max_d; d >= 0; d--) {
			X = BIT(d);
			M = quo * X;
			M += fl_quo * X / 10000;
			/* round step */
			M += (fl_quo * X % 10000) > 5000 ? 1 : 0;
			if (M < 256 && M > 0) {
				unsigned int diff;

				tmp_clock = pll->inputFreq * M / N / X;
				diff = abs(tmp_clock - request_orig);
				if (diff < mini_diff) {
					pll->M = M;
					pll->N = N;
					pll->POD = 0;
					if (d > max_OD)
						pll->POD = d - max_OD;
					pll->OD = d - pll->POD;
					mini_diff = diff;
					ret = tmp_clock;
				}
			}
		}
	}
	return ret;
}