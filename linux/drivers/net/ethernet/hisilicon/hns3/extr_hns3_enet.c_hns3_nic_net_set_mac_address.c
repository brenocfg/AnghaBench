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
struct sockaddr {scalar_t__ sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hnae3_handle {TYPE_2__* ae_algo; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* set_mac_addr ) (struct hnae3_handle*,scalar_t__,int) ;} ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,scalar_t__) ; 
 struct hnae3_handle* hns3_get_handle (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__) ; 
 int stub1 (struct hnae3_handle*,scalar_t__,int) ; 

__attribute__((used)) static int hns3_nic_net_set_mac_address(struct net_device *netdev, void *p)
{
	struct hnae3_handle *h = hns3_get_handle(netdev);
	struct sockaddr *mac_addr = p;
	int ret;

	if (!mac_addr || !is_valid_ether_addr((const u8 *)mac_addr->sa_data))
		return -EADDRNOTAVAIL;

	if (ether_addr_equal(netdev->dev_addr, mac_addr->sa_data)) {
		netdev_info(netdev, "already using mac address %pM\n",
			    mac_addr->sa_data);
		return 0;
	}

	ret = h->ae_algo->ops->set_mac_addr(h, mac_addr->sa_data, false);
	if (ret) {
		netdev_err(netdev, "set_mac_address fail, ret=%d!\n", ret);
		return ret;
	}

	ether_addr_copy(netdev->dev_addr, mac_addr->sa_data);

	return 0;
}