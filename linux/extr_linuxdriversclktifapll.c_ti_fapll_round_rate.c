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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int ti_fapll_set_div_mult (unsigned long,unsigned long,unsigned long*,unsigned long*) ; 

__attribute__((used)) static long ti_fapll_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *parent_rate)
{
	u32 pre_div_p, mult_n;
	int error;

	if (!rate)
		return -EINVAL;

	error = ti_fapll_set_div_mult(rate, *parent_rate,
				      &pre_div_p, &mult_n);
	if (error)
		return error;

	rate = *parent_rate / pre_div_p;
	rate *= mult_n;

	return rate;
}