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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {scalar_t__ link; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethoc {scalar_t__ old_link; scalar_t__ old_duplex; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  MODER ; 
 int /*<<< orphan*/  MODER_FULLD ; 
 int /*<<< orphan*/  ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void ethoc_mdio_poll(struct net_device *dev)
{
	struct ethoc *priv = netdev_priv(dev);
	struct phy_device *phydev = dev->phydev;
	bool changed = false;
	u32 mode;

	if (priv->old_link != phydev->link) {
		changed = true;
		priv->old_link = phydev->link;
	}

	if (priv->old_duplex != phydev->duplex) {
		changed = true;
		priv->old_duplex = phydev->duplex;
	}

	if (!changed)
		return;

	mode = ethoc_read(priv, MODER);
	if (phydev->duplex == DUPLEX_FULL)
		mode |= MODER_FULLD;
	else
		mode &= ~MODER_FULLD;
	ethoc_write(priv, MODER, mode);

	phy_print_status(phydev);
}