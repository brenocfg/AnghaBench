#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct meth_private {unsigned long mac_ctrl; } ;
struct TYPE_3__ {unsigned long mac_ctrl; } ;
struct TYPE_4__ {TYPE_1__ eth; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 unsigned long METH_100MBIT ; 
 unsigned long METH_PHY_FDX ; 
 TYPE_2__* mace ; 
 unsigned long mdio_read (struct meth_private*,int) ; 
 struct meth_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void meth_check_link(struct net_device *dev)
{
	struct meth_private *priv = netdev_priv(dev);
	unsigned long mii_advertising = mdio_read(priv, 4);
	unsigned long mii_partner = mdio_read(priv, 5);
	unsigned long negotiated = mii_advertising & mii_partner;
	unsigned long duplex, speed;

	if (mii_partner == 0xffff)
		return;

	speed = (negotiated & 0x0380) ? METH_100MBIT : 0;
	duplex = ((negotiated & 0x0100) || (negotiated & 0x01C0) == 0x0040) ?
		 METH_PHY_FDX : 0;

	if ((priv->mac_ctrl & METH_PHY_FDX) ^ duplex) {
		DPRINTK("Setting %s-duplex\n", duplex ? "full" : "half");
		if (duplex)
			priv->mac_ctrl |= METH_PHY_FDX;
		else
			priv->mac_ctrl &= ~METH_PHY_FDX;
		mace->eth.mac_ctrl = priv->mac_ctrl;
	}

	if ((priv->mac_ctrl & METH_100MBIT) ^ speed) {
		DPRINTK("Setting %dMbs mode\n", speed ? 100 : 10);
		if (duplex)
			priv->mac_ctrl |= METH_100MBIT;
		else
			priv->mac_ctrl &= ~METH_100MBIT;
		mace->eth.mac_ctrl = priv->mac_ctrl;
	}
}