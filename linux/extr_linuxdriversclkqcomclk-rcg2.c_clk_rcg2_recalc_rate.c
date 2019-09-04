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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ hid_width; scalar_t__ cmd_rcgr; TYPE_1__ clkr; scalar_t__ mnd_width; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int CFG_MODE_MASK ; 
 int CFG_MODE_SHIFT ; 
 scalar_t__ CFG_REG ; 
 int CFG_SRC_DIV_SHIFT ; 
 scalar_t__ M_REG ; 
 scalar_t__ N_REG ; 
 unsigned long calc_rate (unsigned long,int,int,int,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_rcg2_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	u32 cfg, hid_div, m = 0, n = 0, mode = 0, mask;

	regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);

	if (rcg->mnd_width) {
		mask = BIT(rcg->mnd_width) - 1;
		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + M_REG, &m);
		m &= mask;
		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + N_REG, &n);
		n =  ~n;
		n &= mask;
		n += m;
		mode = cfg & CFG_MODE_MASK;
		mode >>= CFG_MODE_SHIFT;
	}

	mask = BIT(rcg->hid_width) - 1;
	hid_div = cfg >> CFG_SRC_DIV_SHIFT;
	hid_div &= mask;

	return calc_rate(parent_rate, m, n, mode, hid_div);
}