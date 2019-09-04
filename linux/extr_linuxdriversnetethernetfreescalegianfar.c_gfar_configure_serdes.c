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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int /*<<< orphan*/  tbi_node; } ;

/* Variables and functions */
 int ADVERTISE_1000XFULL ; 
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_TBICON ; 
 int TBICON_CLK_SELECT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_find_device (int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfar_configure_serdes(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	struct phy_device *tbiphy;

	if (!priv->tbi_node) {
		dev_warn(&dev->dev, "error: SGMII mode requires that the "
				    "device tree specify a tbi-handle\n");
		return;
	}

	tbiphy = of_phy_find_device(priv->tbi_node);
	if (!tbiphy) {
		dev_err(&dev->dev, "error: Could not get TBI device\n");
		return;
	}

	/* If the link is already up, we must already be ok, and don't need to
	 * configure and reset the TBI<->SerDes link.  Maybe U-Boot configured
	 * everything for us?  Resetting it takes the link down and requires
	 * several seconds for it to come back.
	 */
	if (phy_read(tbiphy, MII_BMSR) & BMSR_LSTATUS) {
		put_device(&tbiphy->mdio.dev);
		return;
	}

	/* Single clk mode, mii mode off(for serdes communication) */
	phy_write(tbiphy, MII_TBICON, TBICON_CLK_SELECT);

	phy_write(tbiphy, MII_ADVERTISE,
		  ADVERTISE_1000XFULL | ADVERTISE_1000XPAUSE |
		  ADVERTISE_1000XPSE_ASYM);

	phy_write(tbiphy, MII_BMCR,
		  BMCR_ANENABLE | BMCR_ANRESTART | BMCR_FULLDPLX |
		  BMCR_SPEED1000);

	put_device(&tbiphy->mdio.dev);
}