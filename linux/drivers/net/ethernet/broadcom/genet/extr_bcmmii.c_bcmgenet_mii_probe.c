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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; int /*<<< orphan*/  dev_flags; } ;
struct net_device {struct phy_device* phydev; } ;
struct device_node {int dummy; } ;
struct bcmgenet_priv {int old_link; int old_speed; int old_duplex; int old_pause; scalar_t__ internal_phy; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_dn; int /*<<< orphan*/  gphy_rev; TYPE_2__* pdev; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GENET_IS_V5 (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  PHY_IGNORE_INTERRUPT ; 
 int bcmgenet_mii_config (struct net_device*,int) ; 
 int /*<<< orphan*/  bcmgenet_mii_setup ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcmgenet_priv* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int bcmgenet_mii_probe(struct net_device *dev)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct device_node *dn = priv->pdev->dev.of_node;
	struct phy_device *phydev;
	u32 phy_flags = 0;
	int ret;

	/* Communicate the integrated PHY revision */
	if (priv->internal_phy)
		phy_flags = priv->gphy_rev;

	/* Initialize link state variables that bcmgenet_mii_setup() uses */
	priv->old_link = -1;
	priv->old_speed = -1;
	priv->old_duplex = -1;
	priv->old_pause = -1;

	if (dn) {
		phydev = of_phy_connect(dev, priv->phy_dn, bcmgenet_mii_setup,
					phy_flags, priv->phy_interface);
		if (!phydev) {
			pr_err("could not attach to PHY\n");
			return -ENODEV;
		}
	} else {
		phydev = dev->phydev;
		phydev->dev_flags = phy_flags;

		ret = phy_connect_direct(dev, phydev, bcmgenet_mii_setup,
					 priv->phy_interface);
		if (ret) {
			pr_err("could not attach to PHY\n");
			return -ENODEV;
		}
	}

	/* Configure port multiplexer based on what the probed PHY device since
	 * reading the 'max-speed' property determines the maximum supported
	 * PHY speed which is needed for bcmgenet_mii_config() to configure
	 * things appropriately.
	 */
	ret = bcmgenet_mii_config(dev, true);
	if (ret) {
		phy_disconnect(dev->phydev);
		return ret;
	}

	linkmode_copy(phydev->advertising, phydev->supported);

	/* The internal PHY has its link interrupts routed to the
	 * Ethernet MAC ISRs. On GENETv5 there is a hardware issue
	 * that prevents the signaling of link UP interrupts when
	 * the link operates at 10Mbps, so fallback to polling for
	 * those versions of GENET.
	 */
	if (priv->internal_phy && !GENET_IS_V5(priv))
		dev->phydev->irq = PHY_IGNORE_INTERRUPT;

	return 0;
}