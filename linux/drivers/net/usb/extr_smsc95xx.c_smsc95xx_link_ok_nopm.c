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
struct mii_if_info {int /*<<< orphan*/  phy_id; } ;
struct usbnet {int /*<<< orphan*/  net; struct mii_if_info mii; } ;

/* Variables and functions */
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int smsc95xx_mdio_read_nopm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc95xx_link_ok_nopm(struct usbnet *dev)
{
	struct mii_if_info *mii = &dev->mii;
	int ret;

	/* first, a dummy read, needed to latch some MII phys */
	ret = smsc95xx_mdio_read_nopm(dev->net, mii->phy_id, MII_BMSR);
	if (ret < 0)
		return ret;

	ret = smsc95xx_mdio_read_nopm(dev->net, mii->phy_id, MII_BMSR);
	if (ret < 0)
		return ret;

	return !!(ret & BMSR_LSTATUS);
}