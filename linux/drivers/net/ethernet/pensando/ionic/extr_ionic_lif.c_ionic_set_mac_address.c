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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr {scalar_t__ sa_data; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_commit_mac_addr_change (struct net_device*,struct sockaddr*) ; 
 int eth_prepare_mac_addr_change (struct net_device*,struct sockaddr*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ionic_addr_add (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ionic_addr_del (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ionic_set_mac_address(struct net_device *netdev, void *sa)
{
	struct sockaddr *addr = sa;
	u8 *mac;
	int err;

	mac = (u8 *)addr->sa_data;
	if (ether_addr_equal(netdev->dev_addr, mac))
		return 0;

	err = eth_prepare_mac_addr_change(netdev, addr);
	if (err)
		return err;

	if (!is_zero_ether_addr(netdev->dev_addr)) {
		netdev_info(netdev, "deleting mac addr %pM\n",
			    netdev->dev_addr);
		ionic_addr_del(netdev, netdev->dev_addr);
	}

	eth_commit_mac_addr_change(netdev, addr);
	netdev_info(netdev, "updating mac addr %pM\n", mac);

	return ionic_addr_add(netdev, mac);
}