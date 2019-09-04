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
struct sun6i_dphy {int /*<<< orphan*/  regs; int /*<<< orphan*/  mod_clk; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int SUN6I_DPHY_GCTL_EN ; 
 int SUN6I_DPHY_GCTL_LANE_NUM (unsigned int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_GCTL_REG ; 
 int SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_CTL_REG ; 
 int SUN6I_DPHY_TX_TIME0_HS_PREPARE (int) ; 
 int SUN6I_DPHY_TX_TIME0_HS_TRAIL (int) ; 
 int SUN6I_DPHY_TX_TIME0_LP_CLK_DIV (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME0_REG ; 
 int SUN6I_DPHY_TX_TIME1_CLK_POST (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_PRE (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_PREPARE (int) ; 
 int SUN6I_DPHY_TX_TIME1_CLK_ZERO (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME1_REG ; 
 int SUN6I_DPHY_TX_TIME2_CLK_TRAIL (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME2_REG ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME3_REG ; 
 int SUN6I_DPHY_TX_TIME4_HS_TX_ANA0 (int) ; 
 int SUN6I_DPHY_TX_TIME4_HS_TX_ANA1 (int) ; 
 int /*<<< orphan*/  SUN6I_DPHY_TX_TIME4_REG ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate_exclusive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

int sun6i_dphy_init(struct sun6i_dphy *dphy, unsigned int lanes)
{
	reset_control_deassert(dphy->reset);
	clk_prepare_enable(dphy->mod_clk);
	clk_set_rate_exclusive(dphy->mod_clk, 150000000);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_CTL_REG,
		     SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME0_REG,
		     SUN6I_DPHY_TX_TIME0_LP_CLK_DIV(14) |
		     SUN6I_DPHY_TX_TIME0_HS_PREPARE(6) |
		     SUN6I_DPHY_TX_TIME0_HS_TRAIL(10));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME1_REG,
		     SUN6I_DPHY_TX_TIME1_CLK_PREPARE(7) |
		     SUN6I_DPHY_TX_TIME1_CLK_ZERO(50) |
		     SUN6I_DPHY_TX_TIME1_CLK_PRE(3) |
		     SUN6I_DPHY_TX_TIME1_CLK_POST(10));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME2_REG,
		     SUN6I_DPHY_TX_TIME2_CLK_TRAIL(30));

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME3_REG, 0);

	regmap_write(dphy->regs, SUN6I_DPHY_TX_TIME4_REG,
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(3) |
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(3));

	regmap_write(dphy->regs, SUN6I_DPHY_GCTL_REG,
		     SUN6I_DPHY_GCTL_LANE_NUM(lanes) |
		     SUN6I_DPHY_GCTL_EN);

	return 0;
}