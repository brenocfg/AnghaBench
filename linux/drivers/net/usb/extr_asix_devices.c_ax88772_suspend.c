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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct usbnet {TYPE_1__ mii; int /*<<< orphan*/  net; struct asix_common_private* driver_priv; } ;
struct asix_common_private {void* presvd_phy_advertise; void* presvd_phy_bmcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX_MEDIUM_RE ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 void* asix_mdio_read_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_read_medium_status (struct usbnet*,int) ; 
 int /*<<< orphan*/  asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ax88772_suspend(struct usbnet *dev)
{
	struct asix_common_private *priv = dev->driver_priv;
	u16 medium;

	/* Stop MAC operation */
	medium = asix_read_medium_status(dev, 1);
	medium &= ~AX_MEDIUM_RE;
	asix_write_medium_mode(dev, medium, 1);

	netdev_dbg(dev->net, "ax88772_suspend: medium=0x%04x\n",
		   asix_read_medium_status(dev, 1));

	/* Preserve BMCR for restoring */
	priv->presvd_phy_bmcr =
		asix_mdio_read_nopm(dev->net, dev->mii.phy_id, MII_BMCR);

	/* Preserve ANAR for restoring */
	priv->presvd_phy_advertise =
		asix_mdio_read_nopm(dev->net, dev->mii.phy_id, MII_ADVERTISE);
}