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
typedef  int u32 ;
struct phy_device {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; scalar_t__ pause; } ;
struct net_device {struct phy_device* phydev; } ;
struct bcmgenet_priv {scalar_t__ old_link; scalar_t__ old_speed; scalar_t__ old_duplex; scalar_t__ old_pause; } ;

/* Variables and functions */
 int CMD_HD_EN ; 
 int CMD_RX_PAUSE_IGNORE ; 
 int CMD_SPEED_MASK ; 
 int CMD_SPEED_SHIFT ; 
 int CMD_TX_PAUSE_IGNORE ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  EXT_RGMII_OOB_CTRL ; 
 int OOB_DISABLE ; 
 int RGMII_LINK ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  UMAC_CMD ; 
 int UMAC_SPEED_10 ; 
 int UMAC_SPEED_100 ; 
 int UMAC_SPEED_1000 ; 
 int bcmgenet_ext_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_ext_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 int bcmgenet_umac_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_umac_writel (struct bcmgenet_priv*,int,int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

void bcmgenet_mii_setup(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	u32 reg, cmd_bits = 0;
	bool status_changed = false;

	if (priv->old_link != phydev->link) {
		status_changed = true;
		priv->old_link = phydev->link;
	}

	if (phydev->link) {
		/* check speed/duplex/pause changes */
		if (priv->old_speed != phydev->speed) {
			status_changed = true;
			priv->old_speed = phydev->speed;
		}

		if (priv->old_duplex != phydev->duplex) {
			status_changed = true;
			priv->old_duplex = phydev->duplex;
		}

		if (priv->old_pause != phydev->pause) {
			status_changed = true;
			priv->old_pause = phydev->pause;
		}

		/* done if nothing has changed */
		if (!status_changed)
			return;

		/* speed */
		if (phydev->speed == SPEED_1000)
			cmd_bits = UMAC_SPEED_1000;
		else if (phydev->speed == SPEED_100)
			cmd_bits = UMAC_SPEED_100;
		else
			cmd_bits = UMAC_SPEED_10;
		cmd_bits <<= CMD_SPEED_SHIFT;

		/* duplex */
		if (phydev->duplex != DUPLEX_FULL)
			cmd_bits |= CMD_HD_EN;

		/* pause capability */
		if (!phydev->pause)
			cmd_bits |= CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE;

		/*
		 * Program UMAC and RGMII block based on established
		 * link speed, duplex, and pause. The speed set in
		 * umac->cmd tell RGMII block which clock to use for
		 * transmit -- 25MHz(100Mbps) or 125MHz(1Gbps).
		 * Receive clock is provided by the PHY.
		 */
		reg = bcmgenet_ext_readl(priv, EXT_RGMII_OOB_CTRL);
		reg &= ~OOB_DISABLE;
		reg |= RGMII_LINK;
		bcmgenet_ext_writel(priv, reg, EXT_RGMII_OOB_CTRL);

		reg = bcmgenet_umac_readl(priv, UMAC_CMD);
		reg &= ~((CMD_SPEED_MASK << CMD_SPEED_SHIFT) |
			       CMD_HD_EN |
			       CMD_RX_PAUSE_IGNORE | CMD_TX_PAUSE_IGNORE);
		reg |= cmd_bits;
		bcmgenet_umac_writel(priv, reg, UMAC_CMD);
	} else {
		/* done if nothing has changed */
		if (!status_changed)
			return;

		/* needed for MoCA fixed PHY to reflect correct link status */
		netif_carrier_off(dev);
	}

	phy_print_status(phydev);
}