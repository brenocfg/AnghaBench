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
struct clk_ops {long (* round_rate ) (struct clk_hw*,unsigned long,unsigned long*) ;} ;
struct clk_hw {int dummy; } ;
struct clk_composite {struct clk_hw* rate_hw; struct clk_ops* rate_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hw_set_clk (struct clk_hw*,struct clk_hw*) ; 
 long stub1 (struct clk_hw*,unsigned long,unsigned long*) ; 
 struct clk_composite* to_clk_composite (struct clk_hw*) ; 

__attribute__((used)) static long clk_composite_round_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long *prate)
{
	struct clk_composite *composite = to_clk_composite(hw);
	const struct clk_ops *rate_ops = composite->rate_ops;
	struct clk_hw *rate_hw = composite->rate_hw;

	__clk_hw_set_clk(rate_hw, hw);

	return rate_ops->round_rate(rate_hw, rate, prate);
}