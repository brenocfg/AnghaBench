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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned int div_factor_to_div (unsigned int) ; 
 unsigned int div_to_div_factor (unsigned int) ; 

__attribute__((used)) static long clk_spmi_pmic_div_round_rate(struct clk_hw *hw, unsigned long rate,
					 unsigned long *parent_rate)
{
	unsigned int div, div_factor;

	div = DIV_ROUND_UP(*parent_rate, rate);
	div_factor = div_to_div_factor(div);
	div = div_factor_to_div(div_factor);

	return *parent_rate / div;
}