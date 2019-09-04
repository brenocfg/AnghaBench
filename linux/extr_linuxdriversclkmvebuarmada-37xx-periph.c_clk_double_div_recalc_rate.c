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
typedef  int /*<<< orphan*/  u64 ;
struct clk_hw {int dummy; } ;
struct clk_double_div {int /*<<< orphan*/  shift2; int /*<<< orphan*/  reg2; int /*<<< orphan*/  shift1; int /*<<< orphan*/  reg1; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_double_div* to_clk_double_div (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_double_div_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_double_div *double_div = to_clk_double_div(hw);
	unsigned int div;

	div = get_div(double_div->reg1, double_div->shift1);
	div *= get_div(double_div->reg2, double_div->shift2);

	return DIV_ROUND_UP_ULL((u64)parent_rate, div);
}