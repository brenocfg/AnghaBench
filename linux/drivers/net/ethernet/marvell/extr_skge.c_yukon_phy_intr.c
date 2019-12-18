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
typedef  int u16 ;
struct skge_port {int port; scalar_t__ duplex; scalar_t__ speed; scalar_t__ flow_status; TYPE_1__* netdev; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 scalar_t__ FLOW_STAT_LOC_SEND ; 
 scalar_t__ FLOW_STAT_NONE ; 
 scalar_t__ FLOW_STAT_REM_SEND ; 
 scalar_t__ FLOW_STAT_SYMMETRIC ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMC_PAUSE_OFF ; 
 int /*<<< orphan*/  GMC_PAUSE_ON ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int PHY_B_1000S_MSF ; 
 int /*<<< orphan*/  PHY_MARV_1000T_STAT ; 
 int /*<<< orphan*/  PHY_MARV_AUNE_LP ; 
 int /*<<< orphan*/  PHY_MARV_INT_STAT ; 
 int /*<<< orphan*/  PHY_MARV_PHY_STAT ; 
 int PHY_M_AN_RF ; 
 int PHY_M_IS_AN_COMPL ; 
 int PHY_M_IS_DUP_CHANGE ; 
 int PHY_M_IS_LSP_CHANGE ; 
 int PHY_M_IS_LST_CHANGE ; 
 int PHY_M_PS_FULL_DUP ; 
 int PHY_M_PS_LINK_UP ; 
#define  PHY_M_PS_PAUSE_MSK 130 
#define  PHY_M_PS_RX_P_EN 129 
 int PHY_M_PS_SPDUP_RES ; 
#define  PHY_M_PS_TX_P_EN 128 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SPEED_1000 ; 
 int gm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yukon_link_down (struct skge_port*) ; 
 int /*<<< orphan*/  yukon_link_up (struct skge_port*) ; 
 void* yukon_speed (struct skge_hw*,int) ; 

__attribute__((used)) static void yukon_phy_intr(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	const char *reason = NULL;
	u16 istatus, phystat;

	istatus = gm_phy_read(hw, port, PHY_MARV_INT_STAT);
	phystat = gm_phy_read(hw, port, PHY_MARV_PHY_STAT);

	netif_printk(skge, intr, KERN_DEBUG, skge->netdev,
		     "phy interrupt status 0x%x 0x%x\n", istatus, phystat);

	if (istatus & PHY_M_IS_AN_COMPL) {
		if (gm_phy_read(hw, port, PHY_MARV_AUNE_LP)
		    & PHY_M_AN_RF) {
			reason = "remote fault";
			goto failed;
		}

		if (gm_phy_read(hw, port, PHY_MARV_1000T_STAT) & PHY_B_1000S_MSF) {
			reason = "master/slave fault";
			goto failed;
		}

		if (!(phystat & PHY_M_PS_SPDUP_RES)) {
			reason = "speed/duplex";
			goto failed;
		}

		skge->duplex = (phystat & PHY_M_PS_FULL_DUP)
			? DUPLEX_FULL : DUPLEX_HALF;
		skge->speed = yukon_speed(hw, phystat);

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		switch (phystat & PHY_M_PS_PAUSE_MSK) {
		case PHY_M_PS_PAUSE_MSK:
			skge->flow_status = FLOW_STAT_SYMMETRIC;
			break;
		case PHY_M_PS_RX_P_EN:
			skge->flow_status = FLOW_STAT_REM_SEND;
			break;
		case PHY_M_PS_TX_P_EN:
			skge->flow_status = FLOW_STAT_LOC_SEND;
			break;
		default:
			skge->flow_status = FLOW_STAT_NONE;
		}

		if (skge->flow_status == FLOW_STAT_NONE ||
		    (skge->speed < SPEED_1000 && skge->duplex == DUPLEX_HALF))
			skge_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_OFF);
		else
			skge_write8(hw, SK_REG(port, GMAC_CTRL), GMC_PAUSE_ON);
		yukon_link_up(skge);
		return;
	}

	if (istatus & PHY_M_IS_LSP_CHANGE)
		skge->speed = yukon_speed(hw, phystat);

	if (istatus & PHY_M_IS_DUP_CHANGE)
		skge->duplex = (phystat & PHY_M_PS_FULL_DUP) ? DUPLEX_FULL : DUPLEX_HALF;
	if (istatus & PHY_M_IS_LST_CHANGE) {
		if (phystat & PHY_M_PS_LINK_UP)
			yukon_link_up(skge);
		else
			yukon_link_down(skge);
	}
	return;
 failed:
	pr_err("%s: autonegotiation failed (%s)\n", skge->netdev->name, reason);

	/* XXX restart autonegotiation? */
}