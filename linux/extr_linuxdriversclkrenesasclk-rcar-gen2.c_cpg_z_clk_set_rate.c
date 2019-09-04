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
typedef  int u64 ;
typedef  int u32 ;
struct cpg_z_clk {int /*<<< orphan*/  kick_reg; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CPG_FRQCRB_KICK ; 
 int CPG_FRQCRC_ZFC_MASK ; 
 int CPG_FRQCRC_ZFC_SHIFT ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned int div_u64 (int,unsigned long) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct cpg_z_clk* to_z_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpg_z_clk_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct cpg_z_clk *zclk = to_z_clk(hw);
	unsigned int mult;
	u32 val, kick;
	unsigned int i;

	mult = div_u64((u64)rate * 32, parent_rate);
	mult = clamp(mult, 1U, 32U);

	if (readl(zclk->kick_reg) & CPG_FRQCRB_KICK)
		return -EBUSY;

	val = readl(zclk->reg);
	val &= ~CPG_FRQCRC_ZFC_MASK;
	val |= (32 - mult) << CPG_FRQCRC_ZFC_SHIFT;
	writel(val, zclk->reg);

	/*
	 * Set KICK bit in FRQCRB to update hardware setting and wait for
	 * clock change completion.
	 */
	kick = readl(zclk->kick_reg);
	kick |= CPG_FRQCRB_KICK;
	writel(kick, zclk->kick_reg);

	/*
	 * Note: There is no HW information about the worst case latency.
	 *
	 * Using experimental measurements, it seems that no more than
	 * ~10 iterations are needed, independently of the CPU rate.
	 * Since this value might be dependent on external xtal rate, pll1
	 * rate or even the other emulation clocks rate, use 1000 as a
	 * "super" safe value.
	 */
	for (i = 1000; i; i--) {
		if (!(readl(zclk->kick_reg) & CPG_FRQCRB_KICK))
			return 0;

		cpu_relax();
	}

	return -ETIMEDOUT;
}