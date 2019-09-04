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
struct phy_device {int autoneg; int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; scalar_t__ dev_flags; } ;
struct net_device {int dummy; } ;
struct hnae_handle {int /*<<< orphan*/  phy_if; int /*<<< orphan*/  if_support; struct phy_device* phy_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  hns_nic_adjust_link ; 
 int phy_attach_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_connect_direct (struct net_device*,struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (struct phy_device*) ; 
 scalar_t__ unlikely (int) ; 

int hns_nic_init_phy(struct net_device *ndev, struct hnae_handle *h)
{
	struct phy_device *phy_dev = h->phy_dev;
	int ret;

	if (!h->phy_dev)
		return 0;

	if (h->phy_if != PHY_INTERFACE_MODE_XGMII) {
		phy_dev->dev_flags = 0;

		ret = phy_connect_direct(ndev, phy_dev, hns_nic_adjust_link,
					 h->phy_if);
	} else {
		ret = phy_attach_direct(ndev, phy_dev, 0, h->phy_if);
	}
	if (unlikely(ret))
		return -ENODEV;

	phy_dev->supported &= h->if_support;
	phy_dev->advertising = phy_dev->supported;

	if (h->phy_if == PHY_INTERFACE_MODE_XGMII)
		phy_dev->autoneg = false;

	if (h->phy_if == PHY_INTERFACE_MODE_SGMII)
		phy_stop(phy_dev);

	return 0;
}