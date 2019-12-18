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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; TYPE_1__ mii; int /*<<< orphan*/  data; } ;
struct asix_data {scalar_t__ ledmode; } ;

/* Variables and functions */
 int MARVELL_CTRL_RXDELAY ; 
 int MARVELL_CTRL_TXDELAY ; 
 int /*<<< orphan*/  MII_MARVELL_CTRL ; 
 int /*<<< orphan*/  MII_MARVELL_LED_CTRL ; 
 int /*<<< orphan*/  MII_MARVELL_STATUS ; 
 int asix_mdio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int marvell_phy_init(struct usbnet *dev)
{
	struct asix_data *data = (struct asix_data *)&dev->data;
	u16 reg;

	netdev_dbg(dev->net, "marvell_phy_init()\n");

	reg = asix_mdio_read(dev->net, dev->mii.phy_id, MII_MARVELL_STATUS);
	netdev_dbg(dev->net, "MII_MARVELL_STATUS = 0x%04x\n", reg);

	asix_mdio_write(dev->net, dev->mii.phy_id, MII_MARVELL_CTRL,
			MARVELL_CTRL_RXDELAY | MARVELL_CTRL_TXDELAY);

	if (data->ledmode) {
		reg = asix_mdio_read(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL);
		netdev_dbg(dev->net, "MII_MARVELL_LED_CTRL (1) = 0x%04x\n", reg);

		reg &= 0xf8ff;
		reg |= (1 + 0x0100);
		asix_mdio_write(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL, reg);

		reg = asix_mdio_read(dev->net, dev->mii.phy_id,
			MII_MARVELL_LED_CTRL);
		netdev_dbg(dev->net, "MII_MARVELL_LED_CTRL (2) = 0x%04x\n", reg);
		reg &= 0xfc0f;
	}

	return 0;
}