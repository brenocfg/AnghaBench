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
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_G_EPFBLPR (int) ; 
 scalar_t__ ENETC_G_EPFBLPR1_XGMII ; 
 int ENETC_MAC_MAXFRM_SIZE ; 
 int /*<<< orphan*/  ENETC_PM0_CMD_CFG ; 
 int ENETC_PM0_CMD_PHY_TX_EN ; 
 int ENETC_PM0_CMD_TXP ; 
 int ENETC_PM0_IFM_RGAUTO ; 
 int ENETC_PM0_IFM_XGMII ; 
 int /*<<< orphan*/  ENETC_PM0_IF_MODE ; 
 int /*<<< orphan*/  ENETC_PM0_MAXFRM ; 
 int ENETC_PM0_PROMISC ; 
 int ENETC_PM0_RX_EN ; 
 int ENETC_PM0_TX_EN ; 
 int /*<<< orphan*/  ENETC_PM1_CMD_CFG ; 
 int ENETC_PMO_IFM_RG ; 
 int /*<<< orphan*/  ENETC_PTCMSDUR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETC_PTXMBAR ; 
 int /*<<< orphan*/  ENETC_RX_MAXFRM_SIZE ; 
 int ENETC_SET_MAXFRM (int /*<<< orphan*/ ) ; 
 scalar_t__ enetc_global_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int enetc_port_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enetc_configure_port_mac(struct enetc_hw *hw)
{
	enetc_port_wr(hw, ENETC_PM0_MAXFRM,
		      ENETC_SET_MAXFRM(ENETC_RX_MAXFRM_SIZE));

	enetc_port_wr(hw, ENETC_PTCMSDUR(0), ENETC_MAC_MAXFRM_SIZE);
	enetc_port_wr(hw, ENETC_PTXMBAR, 2 * ENETC_MAC_MAXFRM_SIZE);

	enetc_port_wr(hw, ENETC_PM0_CMD_CFG, ENETC_PM0_CMD_PHY_TX_EN |
		      ENETC_PM0_CMD_TXP	| ENETC_PM0_PROMISC |
		      ENETC_PM0_TX_EN | ENETC_PM0_RX_EN);

	enetc_port_wr(hw, ENETC_PM1_CMD_CFG, ENETC_PM0_CMD_PHY_TX_EN |
		      ENETC_PM0_CMD_TXP	| ENETC_PM0_PROMISC |
		      ENETC_PM0_TX_EN | ENETC_PM0_RX_EN);
	/* set auto-speed for RGMII */
	if (enetc_port_rd(hw, ENETC_PM0_IF_MODE) & ENETC_PMO_IFM_RG)
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, ENETC_PM0_IFM_RGAUTO);
	if (enetc_global_rd(hw, ENETC_G_EPFBLPR(1)) == ENETC_G_EPFBLPR1_XGMII)
		enetc_port_wr(hw, ENETC_PM0_IF_MODE, ENETC_PM0_IFM_XGMII);
}