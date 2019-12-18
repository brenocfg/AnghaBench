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
typedef  int u16 ;
struct skge_port {int port; scalar_t__ autoneg; scalar_t__ flow_control; int /*<<< orphan*/  speed; int /*<<< orphan*/  flow_status; int /*<<< orphan*/  duplex; struct skge_hw* hw; } ;
struct skge_hw {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ FLOW_MODE_LOC_SEND ; 
 scalar_t__ FLOW_MODE_SYMMETRIC ; 
 scalar_t__ FLOW_MODE_SYM_OR_REM ; 
 int /*<<< orphan*/  FLOW_STAT_LOC_SEND ; 
 int /*<<< orphan*/  FLOW_STAT_NONE ; 
 int /*<<< orphan*/  FLOW_STAT_REM_SEND ; 
 int /*<<< orphan*/  FLOW_STAT_SYMMETRIC ; 
 int PHY_B_AN_RF ; 
 int PHY_ST_AN_OVER ; 
 int PHY_ST_LSYNC ; 
 int /*<<< orphan*/  PHY_XMAC_AUNE_LP ; 
 int /*<<< orphan*/  PHY_XMAC_RES_ABI ; 
 int /*<<< orphan*/  PHY_XMAC_STAT ; 
 int PHY_X_P_ASYM_MD ; 
 int PHY_X_P_BOTH_MD ; 
 int PHY_X_P_SYM_MD ; 
#define  PHY_X_RS_FD 129 
#define  PHY_X_RS_HD 128 
 int PHY_X_RS_PAUSE ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  genesis_link_up (struct skge_port*) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  xm_link_down (struct skge_hw*,int) ; 
 int xm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xm_check_link(struct net_device *dev)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 status;

	/* read twice because of latch */
	xm_phy_read(hw, port, PHY_XMAC_STAT);
	status = xm_phy_read(hw, port, PHY_XMAC_STAT);

	if ((status & PHY_ST_LSYNC) == 0) {
		xm_link_down(hw, port);
		return 0;
	}

	if (skge->autoneg == AUTONEG_ENABLE) {
		u16 lpa, res;

		if (!(status & PHY_ST_AN_OVER))
			return 0;

		lpa = xm_phy_read(hw, port, PHY_XMAC_AUNE_LP);
		if (lpa & PHY_B_AN_RF) {
			netdev_notice(dev, "remote fault\n");
			return 0;
		}

		res = xm_phy_read(hw, port, PHY_XMAC_RES_ABI);

		/* Check Duplex mismatch */
		switch (res & (PHY_X_RS_HD | PHY_X_RS_FD)) {
		case PHY_X_RS_FD:
			skge->duplex = DUPLEX_FULL;
			break;
		case PHY_X_RS_HD:
			skge->duplex = DUPLEX_HALF;
			break;
		default:
			netdev_notice(dev, "duplex mismatch\n");
			return 0;
		}

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		if ((skge->flow_control == FLOW_MODE_SYMMETRIC ||
		     skge->flow_control == FLOW_MODE_SYM_OR_REM) &&
		    (lpa & PHY_X_P_SYM_MD))
			skge->flow_status = FLOW_STAT_SYMMETRIC;
		else if (skge->flow_control == FLOW_MODE_SYM_OR_REM &&
			 (lpa & PHY_X_RS_PAUSE) == PHY_X_P_ASYM_MD)
			/* Enable PAUSE receive, disable PAUSE transmit */
			skge->flow_status  = FLOW_STAT_REM_SEND;
		else if (skge->flow_control == FLOW_MODE_LOC_SEND &&
			 (lpa & PHY_X_RS_PAUSE) == PHY_X_P_BOTH_MD)
			/* Disable PAUSE receive, enable PAUSE transmit */
			skge->flow_status = FLOW_STAT_LOC_SEND;
		else
			skge->flow_status = FLOW_STAT_NONE;

		skge->speed = SPEED_1000;
	}

	if (!netif_carrier_ok(dev))
		genesis_link_up(skge);
	return 1;
}