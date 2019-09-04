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
 long DIV_ROUND_UP_ULL (unsigned long,int) ; 
 int pl111_clk_div_choose_div (struct clk_hw*,unsigned long,unsigned long*,int) ; 

__attribute__((used)) static long pl111_clk_div_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	int div = pl111_clk_div_choose_div(hw, rate, prate, true);

	return DIV_ROUND_UP_ULL(*prate, div);
}