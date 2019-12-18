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
struct isc_clk {scalar_t__ div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,scalar_t__) ; 
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
isc_clk_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);

	return DIV_ROUND_CLOSEST(parent_rate, isc_clk->div + 1);
}