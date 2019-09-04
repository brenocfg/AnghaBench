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
struct device {int dummy; } ;
struct clk_hw {struct clk* clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* ERR_CAST (struct clk_hw*) ; 
 scalar_t__ IS_ERR (struct clk_hw*) ; 
 struct clk_hw* clk_hw_register_fixed_factor (struct device*,char const*,char const*,unsigned long,unsigned int,unsigned int) ; 

struct clk *clk_register_fixed_factor(struct device *dev, const char *name,
		const char *parent_name, unsigned long flags,
		unsigned int mult, unsigned int div)
{
	struct clk_hw *hw;

	hw = clk_hw_register_fixed_factor(dev, name, parent_name, flags, mult,
					  div);
	if (IS_ERR(hw))
		return ERR_CAST(hw);
	return hw->clk;
}