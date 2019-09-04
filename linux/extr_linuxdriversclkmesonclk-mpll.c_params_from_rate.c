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
typedef  unsigned int uint64_t ;
typedef  int u8 ;

/* Variables and functions */
 int CLK_MESON_MPLL_ROUND_CLOSEST ; 
 unsigned int DIV_ROUND_CLOSEST_ULL (unsigned int,unsigned long) ; 
 unsigned int DIV_ROUND_UP_ULL (unsigned int,unsigned long) ; 
 unsigned int N2_MAX ; 
 unsigned int N2_MIN ; 
 unsigned int SDM_DEN ; 
 unsigned int do_div (unsigned int,unsigned long) ; 

__attribute__((used)) static void params_from_rate(unsigned long requested_rate,
			     unsigned long parent_rate,
			     unsigned int *sdm,
			     unsigned int *n2,
			     u8 flags)
{
	uint64_t div = parent_rate;
	uint64_t frac = do_div(div, requested_rate);

	frac *= SDM_DEN;

	if (flags & CLK_MESON_MPLL_ROUND_CLOSEST)
		*sdm = DIV_ROUND_CLOSEST_ULL(frac, requested_rate);
	else
		*sdm = DIV_ROUND_UP_ULL(frac, requested_rate);

	if (*sdm == SDM_DEN) {
		*sdm = 0;
		div += 1;
	}

	if (div < N2_MIN) {
		*n2 = N2_MIN;
		*sdm = 0;
	} else if (div > N2_MAX) {
		*n2 = N2_MAX;
		*sdm = SDM_DEN - 1;
	} else {
		*n2 = div;
	}
}