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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_2__ mdio; scalar_t__ link; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct bcmgenet_priv {int phy_interface; int internal_phy; int /*<<< orphan*/  phy_dn; TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_INTERNAL ; 
 int PHY_INTERFACE_MODE_MOCA ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_find_device (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcmgenet_mii_of_init(struct bcmgenet_priv *priv)
{
	struct device_node *dn = priv->pdev->dev.of_node;
	struct device *kdev = &priv->pdev->dev;
	struct phy_device *phydev;
	int phy_mode;
	int ret;

	/* Fetch the PHY phandle */
	priv->phy_dn = of_parse_phandle(dn, "phy-handle", 0);

	/* In the case of a fixed PHY, the DT node associated
	 * to the PHY is the Ethernet MAC DT node.
	 */
	if (!priv->phy_dn && of_phy_is_fixed_link(dn)) {
		ret = of_phy_register_fixed_link(dn);
		if (ret)
			return ret;

		priv->phy_dn = of_node_get(dn);
	}

	/* Get the link mode */
	phy_mode = of_get_phy_mode(dn);
	if (phy_mode < 0) {
		dev_err(kdev, "invalid PHY mode property\n");
		return phy_mode;
	}

	priv->phy_interface = phy_mode;

	/* We need to specifically look up whether this PHY interface is internal
	 * or not *before* we even try to probe the PHY driver over MDIO as we
	 * may have shut down the internal PHY for power saving purposes.
	 */
	if (priv->phy_interface == PHY_INTERFACE_MODE_INTERNAL)
		priv->internal_phy = true;

	/* Make sure we initialize MoCA PHYs with a link down */
	if (phy_mode == PHY_INTERFACE_MODE_MOCA) {
		phydev = of_phy_find_device(dn);
		if (phydev) {
			phydev->link = 0;
			put_device(&phydev->mdio.dev);
		}
	}

	return 0;
}