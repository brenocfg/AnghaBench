#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mn {scalar_t__ width; } ;
struct TYPE_2__ {scalar_t__ enable_reg; int /*<<< orphan*/  regmap; } ;
struct clk_rcg {scalar_t__ ns_reg; scalar_t__ md_reg; TYPE_1__ clkr; struct mn mn; int /*<<< orphan*/  p; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long calc_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_to_m (struct mn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_m_to_n (struct mn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_pre_div (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_to_mnctr_mode (struct mn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 struct clk_rcg* to_clk_rcg (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_rcg_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_rcg *rcg = to_clk_rcg(hw);
	u32 pre_div, m = 0, n = 0, ns, md, mode = 0;
	struct mn *mn = &rcg->mn;

	regmap_read(rcg->clkr.regmap, rcg->ns_reg, &ns);
	pre_div = ns_to_pre_div(&rcg->p, ns);

	if (rcg->mn.width) {
		regmap_read(rcg->clkr.regmap, rcg->md_reg, &md);
		m = md_to_m(mn, md);
		n = ns_m_to_n(mn, ns, m);
		/* MN counter mode is in hw.enable_reg sometimes */
		if (rcg->clkr.enable_reg != rcg->ns_reg)
			regmap_read(rcg->clkr.regmap, rcg->clkr.enable_reg, &mode);
		else
			mode = ns;
		mode = reg_to_mnctr_mode(mn, mode);
	}

	return calc_rate(parent_rate, m, n, mode, pre_div);
}