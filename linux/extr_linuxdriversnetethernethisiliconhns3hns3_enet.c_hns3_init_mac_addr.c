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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hns3_nic_priv {int /*<<< orphan*/  dev; struct hnae3_handle* ae_handle; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_mac_addr ) (struct hnae3_handle*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* get_mac_addr ) (struct hnae3_handle*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct hnae3_handle*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns3_init_mac_addr(struct net_device *netdev, bool init)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);
	struct hnae3_handle *h = priv->ae_handle;
	u8 mac_addr_temp[ETH_ALEN];

	if (h->ae_algo->ops->get_mac_addr && init) {
		h->ae_algo->ops->get_mac_addr(h, mac_addr_temp);
		ether_addr_copy(netdev->dev_addr, mac_addr_temp);
	}

	/* Check if the MAC address is valid, if not get a random one */
	if (!is_valid_ether_addr(netdev->dev_addr)) {
		eth_hw_addr_random(netdev);
		dev_warn(priv->dev, "using random MAC address %pM\n",
			 netdev->dev_addr);
	}

	if (h->ae_algo->ops->set_mac_addr)
		h->ae_algo->ops->set_mac_addr(h, netdev->dev_addr, true);

}