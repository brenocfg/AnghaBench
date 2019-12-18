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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_set_hw_mac_address (struct net_device*) ; 

__attribute__((used)) static s32 nps_enet_set_mac_address(struct net_device *ndev, void *p)
{
	struct sockaddr *addr = p;
	s32 res;

	if (netif_running(ndev))
		return -EBUSY;

	res = eth_mac_addr(ndev, p);
	if (!res) {
		ether_addr_copy(ndev->dev_addr, addr->sa_data);
		nps_enet_set_hw_mac_address(ndev);
	}

	return res;
}