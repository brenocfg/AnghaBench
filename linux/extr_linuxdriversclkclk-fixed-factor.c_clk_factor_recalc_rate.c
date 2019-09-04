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
struct clk_fixed_factor {unsigned long long mult; int /*<<< orphan*/  div; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 struct clk_fixed_factor* to_clk_fixed_factor (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_factor_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_fixed_factor *fix = to_clk_fixed_factor(hw);
	unsigned long long int rate;

	rate = (unsigned long long int)parent_rate * fix->mult;
	do_div(rate, fix->div);
	return (unsigned long)rate;
}