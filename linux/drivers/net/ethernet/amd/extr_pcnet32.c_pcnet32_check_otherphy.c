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
typedef  int u16 ;
struct mii_if_info {int phy_id; } ;
struct pcnet32_private {int phymask; struct mii_if_info mii_if; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BMCR_ISOLATE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PCNET32_MAX_PHYS ; 
 int /*<<< orphan*/  link ; 
 int mdio_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mii_link_ok (struct mii_if_info*) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct pcnet32_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 

__attribute__((used)) static int pcnet32_check_otherphy(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	struct mii_if_info mii = lp->mii_if;
	u16 bmcr;
	int i;

	for (i = 0; i < PCNET32_MAX_PHYS; i++) {
		if (i == lp->mii_if.phy_id)
			continue;	/* skip active phy */
		if (lp->phymask & (1 << i)) {
			mii.phy_id = i;
			if (mii_link_ok(&mii)) {
				/* found PHY with active link */
				netif_info(lp, link, dev, "Using PHY number %d\n",
					   i);

				/* isolate inactive phy */
				bmcr =
				    mdio_read(dev, lp->mii_if.phy_id, MII_BMCR);
				mdio_write(dev, lp->mii_if.phy_id, MII_BMCR,
					   bmcr | BMCR_ISOLATE);

				/* de-isolate new phy */
				bmcr = mdio_read(dev, i, MII_BMCR);
				mdio_write(dev, i, MII_BMCR,
					   bmcr & ~BMCR_ISOLATE);

				/* set new phy address */
				lp->mii_if.phy_id = i;
				return 1;
			}
		}
	}
	return 0;
}