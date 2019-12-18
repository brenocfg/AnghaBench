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
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ftgmac100 {int /*<<< orphan*/  mii_bus; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  ftgmac100_adjust_link ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_name (struct phy_device*) ; 

__attribute__((used)) static int ftgmac100_mii_probe(struct ftgmac100 *priv, phy_interface_t intf)
{
	struct net_device *netdev = priv->netdev;
	struct phy_device *phydev;

	phydev = phy_find_first(priv->mii_bus);
	if (!phydev) {
		netdev_info(netdev, "%s: no PHY found\n", netdev->name);
		return -ENODEV;
	}

	phydev = phy_connect(netdev, phydev_name(phydev),
			     &ftgmac100_adjust_link, intf);

	if (IS_ERR(phydev)) {
		netdev_err(netdev, "%s: Could not attach to PHY\n", netdev->name);
		return PTR_ERR(phydev);
	}

	/* Indicate that we support PAUSE frames (see comment in
	 * Documentation/networking/phy.rst)
	 */
	phy_support_asym_pause(phydev);

	/* Display what we found */
	phy_attached_info(phydev);

	return 0;
}