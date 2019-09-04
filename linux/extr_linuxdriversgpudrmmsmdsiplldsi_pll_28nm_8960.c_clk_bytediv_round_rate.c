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
 int /*<<< orphan*/  clk_hw_get_parent (struct clk_hw*) ; 
 unsigned long clk_hw_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int get_vco_mul_factor (unsigned long) ; 

__attribute__((used)) static long clk_bytediv_round_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long *prate)
{
	unsigned long best_parent;
	unsigned int factor;

	factor = get_vco_mul_factor(rate);

	best_parent = rate * factor;
	*prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);

	return *prate / factor;
}