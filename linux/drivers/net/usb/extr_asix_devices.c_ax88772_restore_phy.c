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
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct usbnet {TYPE_1__ mii; int /*<<< orphan*/  net; struct asix_common_private* driver_priv; } ;
struct asix_common_private {int presvd_phy_advertise; int presvd_phy_bmcr; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  asix_mdio_write_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ax88772_restore_phy(struct usbnet *dev)
{
	struct asix_common_private *priv = dev->driver_priv;

	if (priv->presvd_phy_advertise) {
		/* Restore Advertisement control reg */
		asix_mdio_write_nopm(dev->net, dev->mii.phy_id, MII_ADVERTISE,
				     priv->presvd_phy_advertise);

		/* Restore BMCR */
		if (priv->presvd_phy_bmcr & BMCR_ANENABLE)
			priv->presvd_phy_bmcr |= BMCR_ANRESTART;

		asix_mdio_write_nopm(dev->net, dev->mii.phy_id, MII_BMCR,
				     priv->presvd_phy_bmcr);

		priv->presvd_phy_advertise = 0;
		priv->presvd_phy_bmcr = 0;
	}
}