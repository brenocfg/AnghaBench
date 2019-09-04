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
typedef  unsigned int u64 ;
struct cpg_z_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int CPG_FRQCRC_ZFC_MASK ; 
 unsigned int CPG_FRQCRC_ZFC_SHIFT ; 
 unsigned long div_u64 (unsigned int,int) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 struct cpg_z_clk* to_z_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long cpg_z_clk_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct cpg_z_clk *zclk = to_z_clk(hw);
	unsigned int mult;
	unsigned int val;

	val = (readl(zclk->reg) & CPG_FRQCRC_ZFC_MASK) >> CPG_FRQCRC_ZFC_SHIFT;
	mult = 32 - val;

	return div_u64((u64)parent_rate * mult, 32);
}