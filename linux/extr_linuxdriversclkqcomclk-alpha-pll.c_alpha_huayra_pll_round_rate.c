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

/* Variables and functions */
 int BIT (int) ; 
 int PLL_HUAYRA_ALPHA_WIDTH ; 
 unsigned long alpha_huayra_pll_calc_rate (unsigned long,int,int) ; 
 int do_div (int,unsigned long) ; 

__attribute__((used)) static unsigned long
alpha_huayra_pll_round_rate(unsigned long rate, unsigned long prate,
			    u32 *l, u32 *a)
{
	u64 remainder;
	u64 quotient;

	quotient = rate;
	remainder = do_div(quotient, prate);
	*l = quotient;

	if (!remainder) {
		*a = 0;
		return rate;
	}

	quotient = remainder << PLL_HUAYRA_ALPHA_WIDTH;
	remainder = do_div(quotient, prate);

	if (remainder)
		quotient++;

	/*
	 * alpha_val should be in two’s compliment number in the range
	 * of [-0.5, 0.5) so if quotient >= 0.5 then increment the l value
	 * since alpha value will be subtracted in this case.
	 */
	if (quotient >= BIT(PLL_HUAYRA_ALPHA_WIDTH - 1))
		*l += 1;

	*a = quotient;
	return alpha_huayra_pll_calc_rate(prate, *l, *a);
}