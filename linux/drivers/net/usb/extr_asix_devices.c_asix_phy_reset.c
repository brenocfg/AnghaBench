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
struct usbnet {TYPE_1__ mii; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int asix_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void asix_phy_reset(struct usbnet *dev, unsigned int reset_bits)
{
	unsigned int timeout = 5000;

	asix_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, reset_bits);

	/* give phy_id a chance to process reset */
	udelay(500);

	/* See IEEE 802.3 "22.2.4.1.1 Reset": 500ms max */
	while (timeout--) {
		if (asix_mdio_read(dev->net, dev->mii.phy_id, MII_BMCR)
							& BMCR_RESET)
			udelay(100);
		else
			return;
	}

	netdev_err(dev->net, "BMCR_RESET timeout on phy_id %d\n",
		   dev->mii.phy_id);
}