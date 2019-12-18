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
typedef  scalar_t__ u32 ;
struct isc_clk {scalar_t__ div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EINVAL ; 
 scalar_t__ ISC_CLK_MAX_DIV ; 
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static int isc_clk_set_rate(struct clk_hw *hw,
			     unsigned long rate,
			     unsigned long parent_rate)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);
	u32 div;

	if (!rate)
		return -EINVAL;

	div = DIV_ROUND_CLOSEST(parent_rate, rate);
	if (div > (ISC_CLK_MAX_DIV + 1) || !div)
		return -EINVAL;

	isc_clk->div = div - 1;

	return 0;
}