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
typedef  int /*<<< orphan*/  u16 ;
struct rockchip_typec_phy {scalar_t__ base; int /*<<< orphan*/  flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUXDA_POLARITY ; 
 scalar_t__ TX_ANA_CTRL_REG_1 ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tcphy_dp_aux_set_flip(struct rockchip_typec_phy *tcphy)
{
	u16 tx_ana_ctrl_reg_1;

	/*
	 * Select the polarity of the xcvr:
	 * 1, Reverses the polarity (If TYPEC, Pulls ups aux_p and pull
	 * down aux_m)
	 * 0, Normal polarity (if TYPEC, pulls up aux_m and pulls down
	 * aux_p)
	 */
	tx_ana_ctrl_reg_1 = readl(tcphy->base + TX_ANA_CTRL_REG_1);
	if (!tcphy->flip)
		tx_ana_ctrl_reg_1 |= AUXDA_POLARITY;
	else
		tx_ana_ctrl_reg_1 &= ~AUXDA_POLARITY;
	writel(tx_ana_ctrl_reg_1, tcphy->base + TX_ANA_CTRL_REG_1);
}