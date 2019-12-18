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
struct macvlan_dev {scalar_t__ mode; int /*<<< orphan*/  port; int /*<<< orphan*/  lowerdev; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ MACVLAN_MODE_PASSTHRU ; 
 int dev_set_mac_address (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ macvlan_addr_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_set_addr_change (int /*<<< orphan*/ ) ; 
 int macvlan_sync_address (struct net_device*,int /*<<< orphan*/ ) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_set_mac_address(struct net_device *dev, void *p)
{
	struct macvlan_dev *vlan = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* If the addresses are the same, this is a no-op */
	if (ether_addr_equal(dev->dev_addr, addr->sa_data))
		return 0;

	if (vlan->mode == MACVLAN_MODE_PASSTHRU) {
		macvlan_set_addr_change(vlan->port);
		return dev_set_mac_address(vlan->lowerdev, addr, NULL);
	}

	if (macvlan_addr_busy(vlan->port, addr->sa_data))
		return -EADDRINUSE;

	return macvlan_sync_address(dev, addr->sa_data);
}