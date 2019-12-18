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
struct phy_device {int duplex; int speed; scalar_t__ link; } ;
struct net_device {int /*<<< orphan*/  name; struct phy_device* phydev; } ;
struct altera_tse_private {int oldduplex; int oldspeed; int oldlink; int /*<<< orphan*/  mac_cfg_lock; TYPE_1__* mac_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  command_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CMDCFG_ENA_10 ; 
 int /*<<< orphan*/  MAC_CMDCFG_ETH_SPEED ; 
 int /*<<< orphan*/  MAC_CMDCFG_HD_ENA ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int) ; 
 scalar_t__ netif_msg_link (struct altera_tse_private*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void altera_tse_adjust_link(struct net_device *dev)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	int new_state = 0;

	/* only change config if there is a link */
	spin_lock(&priv->mac_cfg_lock);
	if (phydev->link) {
		/* Read old config */
		u32 cfg_reg = ioread32(&priv->mac_dev->command_config);

		/* Check duplex */
		if (phydev->duplex != priv->oldduplex) {
			new_state = 1;
			if (!(phydev->duplex))
				cfg_reg |= MAC_CMDCFG_HD_ENA;
			else
				cfg_reg &= ~MAC_CMDCFG_HD_ENA;

			netdev_dbg(priv->dev, "%s: Link duplex = 0x%x\n",
				   dev->name, phydev->duplex);

			priv->oldduplex = phydev->duplex;
		}

		/* Check speed */
		if (phydev->speed != priv->oldspeed) {
			new_state = 1;
			switch (phydev->speed) {
			case 1000:
				cfg_reg |= MAC_CMDCFG_ETH_SPEED;
				cfg_reg &= ~MAC_CMDCFG_ENA_10;
				break;
			case 100:
				cfg_reg &= ~MAC_CMDCFG_ETH_SPEED;
				cfg_reg &= ~MAC_CMDCFG_ENA_10;
				break;
			case 10:
				cfg_reg &= ~MAC_CMDCFG_ETH_SPEED;
				cfg_reg |= MAC_CMDCFG_ENA_10;
				break;
			default:
				if (netif_msg_link(priv))
					netdev_warn(dev, "Speed (%d) is not 10/100/1000!\n",
						    phydev->speed);
				break;
			}
			priv->oldspeed = phydev->speed;
		}
		iowrite32(cfg_reg, &priv->mac_dev->command_config);

		if (!priv->oldlink) {
			new_state = 1;
			priv->oldlink = 1;
		}
	} else if (priv->oldlink) {
		new_state = 1;
		priv->oldlink = 0;
		priv->oldspeed = 0;
		priv->oldduplex = -1;
	}

	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);

	spin_unlock(&priv->mac_cfg_lock);
}