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
struct net_device {int /*<<< orphan*/  dev; } ;
struct enetc_ndev_priv {int /*<<< orphan*/  if_mode; int /*<<< orphan*/  phy_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  adjust_link ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 
 struct phy_device* of_phy_connect (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 

__attribute__((used)) static int enetc_phy_connect(struct net_device *ndev)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct phy_device *phydev;

	if (!priv->phy_node)
		return 0; /* phy-less mode */

	phydev = of_phy_connect(ndev, priv->phy_node, &adjust_link,
				0, priv->if_mode);
	if (!phydev) {
		dev_err(&ndev->dev, "could not attach to PHY\n");
		return -ENODEV;
	}

	phy_attached_info(phydev);

	return 0;
}