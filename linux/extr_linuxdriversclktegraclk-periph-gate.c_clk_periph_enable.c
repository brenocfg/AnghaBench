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
struct tegra_clk_periph_gate {int* enable_refcnt; size_t clk_num; int flags; scalar_t__ clk_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ LVL2_CLK_GATE_OVRE ; 
 int TEGRA_PERIPH_MANUAL_RESET ; 
 int TEGRA_PERIPH_NO_RESET ; 
 int TEGRA_PERIPH_WAR_1005168 ; 
 int periph_clk_to_bit (struct tegra_clk_periph_gate*) ; 
 int /*<<< orphan*/  periph_ref_lock ; 
 int read_rst (struct tegra_clk_periph_gate*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tegra_clk_periph_gate* to_clk_periph_gate (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_enb_set (int,struct tegra_clk_periph_gate*) ; 
 int /*<<< orphan*/  write_rst_clr (int,struct tegra_clk_periph_gate*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int clk_periph_enable(struct clk_hw *hw)
{
	struct tegra_clk_periph_gate *gate = to_clk_periph_gate(hw);
	unsigned long flags = 0;

	spin_lock_irqsave(&periph_ref_lock, flags);

	gate->enable_refcnt[gate->clk_num]++;
	if (gate->enable_refcnt[gate->clk_num] > 1) {
		spin_unlock_irqrestore(&periph_ref_lock, flags);
		return 0;
	}

	write_enb_set(periph_clk_to_bit(gate), gate);
	udelay(2);

	if (!(gate->flags & TEGRA_PERIPH_NO_RESET) &&
	    !(gate->flags & TEGRA_PERIPH_MANUAL_RESET)) {
		if (read_rst(gate) & periph_clk_to_bit(gate)) {
			udelay(5); /* reset propogation delay */
			write_rst_clr(periph_clk_to_bit(gate), gate);
		}
	}

	if (gate->flags & TEGRA_PERIPH_WAR_1005168) {
		writel_relaxed(0, gate->clk_base + LVL2_CLK_GATE_OVRE);
		writel_relaxed(BIT(22), gate->clk_base + LVL2_CLK_GATE_OVRE);
		udelay(1);
		writel_relaxed(0, gate->clk_base + LVL2_CLK_GATE_OVRE);
	}

	spin_unlock_irqrestore(&periph_ref_lock, flags);

	return 0;
}