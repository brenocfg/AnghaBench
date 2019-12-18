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
struct phy_device {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct arc_emac_priv {scalar_t__ link; scalar_t__ speed; scalar_t__ duplex; int /*<<< orphan*/  (* set_mac_speed ) (struct arc_emac_priv*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 unsigned int ENFL_MASK ; 
 int /*<<< orphan*/  R_CTRL ; 
 unsigned int arc_reg_get (struct arc_emac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_reg_set (struct arc_emac_priv*,int /*<<< orphan*/ ,unsigned int) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int /*<<< orphan*/  stub1 (struct arc_emac_priv*,scalar_t__) ; 

__attribute__((used)) static void arc_emac_adjust_link(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);
	struct phy_device *phy_dev = ndev->phydev;
	unsigned int reg, state_changed = 0;

	if (priv->link != phy_dev->link) {
		priv->link = phy_dev->link;
		state_changed = 1;
	}

	if (priv->speed != phy_dev->speed) {
		priv->speed = phy_dev->speed;
		state_changed = 1;
		if (priv->set_mac_speed)
			priv->set_mac_speed(priv, priv->speed);
	}

	if (priv->duplex != phy_dev->duplex) {
		reg = arc_reg_get(priv, R_CTRL);

		if (phy_dev->duplex == DUPLEX_FULL)
			reg |= ENFL_MASK;
		else
			reg &= ~ENFL_MASK;

		arc_reg_set(priv, R_CTRL, reg);
		priv->duplex = phy_dev->duplex;
		state_changed = 1;
	}

	if (state_changed)
		phy_print_status(phy_dev);
}