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
struct stm32_fractional_divider {unsigned long fshift; scalar_t__ fwidth; int /*<<< orphan*/  freg_value; } ;
struct stm32_pll_obj {struct stm32_fractional_divider div; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 struct stm32_pll_obj* to_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long pll_read_frac(struct clk_hw *hw)
{
	struct stm32_pll_obj *clk_elem = to_pll(hw);
	struct stm32_fractional_divider *fd = &clk_elem->div;

	return (readl(fd->freg_value) >> fd->fshift) &
		GENMASK(fd->fwidth - 1, 0);
}