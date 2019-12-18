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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hns_nic_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_mac_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hns_init_mac_addr(struct net_device *ndev)
{
	struct hns_nic_priv *priv = netdev_priv(ndev);

	if (!device_get_mac_address(priv->dev, ndev->dev_addr, ETH_ALEN)) {
		eth_hw_addr_random(ndev);
		dev_warn(priv->dev, "No valid mac, use random mac %pM",
			 ndev->dev_addr);
	}
}