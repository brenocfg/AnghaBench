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
struct skge_port {scalar_t__ autoneg; int /*<<< orphan*/  speed; int /*<<< orphan*/  flow_status; int /*<<< orphan*/  duplex; } ;
struct skge_hw {struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  FLOW_STAT_LOC_SEND ; 
 int /*<<< orphan*/  FLOW_STAT_NONE ; 
 int /*<<< orphan*/  FLOW_STAT_REM_SEND ; 
 int /*<<< orphan*/  FLOW_STAT_SYMMETRIC ; 
 int /*<<< orphan*/  PHY_BCOM_AUX_STAT ; 
 int /*<<< orphan*/  PHY_BCOM_STAT ; 
 int PHY_B_AN_RF ; 
 int PHY_B_AS_AN_RES_MSK ; 
#define  PHY_B_AS_PAUSE_MSK 132 
#define  PHY_B_AS_PRR 131 
#define  PHY_B_AS_PRT 130 
#define  PHY_B_RES_1000FD 129 
#define  PHY_B_RES_1000HD 128 
 int PHY_ST_AN_OVER ; 
 int PHY_ST_LSYNC ; 
 int /*<<< orphan*/  PHY_XMAC_AUNE_LP ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  genesis_link_up (struct skge_port*) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  xm_link_down (struct skge_hw*,int) ; 
 int xm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcom_check_link(struct skge_hw *hw, int port)
{
	struct net_device *dev = hw->dev[port];
	struct skge_port *skge = netdev_priv(dev);
	u16 status;

	/* read twice because of latch */
	xm_phy_read(hw, port, PHY_BCOM_STAT);
	status = xm_phy_read(hw, port, PHY_BCOM_STAT);

	if ((status & PHY_ST_LSYNC) == 0) {
		xm_link_down(hw, port);
		return;
	}

	if (skge->autoneg == AUTONEG_ENABLE) {
		u16 lpa, aux;

		if (!(status & PHY_ST_AN_OVER))
			return;

		lpa = xm_phy_read(hw, port, PHY_XMAC_AUNE_LP);
		if (lpa & PHY_B_AN_RF) {
			netdev_notice(dev, "remote fault\n");
			return;
		}

		aux = xm_phy_read(hw, port, PHY_BCOM_AUX_STAT);

		/* Check Duplex mismatch */
		switch (aux & PHY_B_AS_AN_RES_MSK) {
		case PHY_B_RES_1000FD:
			skge->duplex = DUPLEX_FULL;
			break;
		case PHY_B_RES_1000HD:
			skge->duplex = DUPLEX_HALF;
			break;
		default:
			netdev_notice(dev, "duplex mismatch\n");
			return;
		}

		/* We are using IEEE 802.3z/D5.0 Table 37-4 */
		switch (aux & PHY_B_AS_PAUSE_MSK) {
		case PHY_B_AS_PAUSE_MSK:
			skge->flow_status = FLOW_STAT_SYMMETRIC;
			break;
		case PHY_B_AS_PRR:
			skge->flow_status = FLOW_STAT_REM_SEND;
			break;
		case PHY_B_AS_PRT:
			skge->flow_status = FLOW_STAT_LOC_SEND;
			break;
		default:
			skge->flow_status = FLOW_STAT_NONE;
		}
		skge->speed = SPEED_1000;
	}

	if (!netif_carrier_ok(dev))
		genesis_link_up(skge);
}