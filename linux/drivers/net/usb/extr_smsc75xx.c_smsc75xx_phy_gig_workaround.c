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
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_PHY_RST ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int smsc75xx_link_ok_nopm (struct usbnet*) ; 
 int /*<<< orphan*/  smsc75xx_mdio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int smsc75xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc75xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int smsc75xx_phy_gig_workaround(struct usbnet *dev)
{
	struct mii_if_info *mii = &dev->mii;
	int ret = 0, timeout = 0;
	u32 buf, link_up = 0;

	/* Set the phy in Gig loopback */
	smsc75xx_mdio_write(dev->net, mii->phy_id, MII_BMCR, 0x4040);

	/* Wait for the link up */
	do {
		link_up = smsc75xx_link_ok_nopm(dev);
		usleep_range(10000, 20000);
		timeout++;
	} while ((!link_up) && (timeout < 1000));

	if (timeout >= 1000) {
		netdev_warn(dev->net, "Timeout waiting for PHY link up\n");
		return -EIO;
	}

	/* phy reset */
	ret = smsc75xx_read_reg(dev, PMT_CTL, &buf);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
		return ret;
	}

	buf |= PMT_CTL_PHY_RST;

	ret = smsc75xx_write_reg(dev, PMT_CTL, buf);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to write PMT_CTL: %d\n", ret);
		return ret;
	}

	timeout = 0;
	do {
		usleep_range(10000, 20000);
		ret = smsc75xx_read_reg(dev, PMT_CTL, &buf);
		if (ret < 0) {
			netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n",
				    ret);
			return ret;
		}
		timeout++;
	} while ((buf & PMT_CTL_PHY_RST) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout waiting for PHY Reset\n");
		return -EIO;
	}

	return 0;
}