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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_plt {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  plt_reg_to_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct clk_plt* to_clk_plt (struct clk_hw*) ; 

__attribute__((used)) static u8 plt_clk_get_parent(struct clk_hw *hw)
{
	struct clk_plt *clk = to_clk_plt(hw);
	u32 value;

	value = readl(clk->reg);

	return plt_reg_to_parent(value);
}