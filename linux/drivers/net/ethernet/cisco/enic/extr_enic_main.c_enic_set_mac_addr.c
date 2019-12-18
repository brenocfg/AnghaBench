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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct enic {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ enic_is_dynamic (struct enic*) ; 
 scalar_t__ enic_is_sriov_vf (struct enic*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (char*) ; 
 int /*<<< orphan*/  is_zero_ether_addr (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct enic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enic_set_mac_addr(struct net_device *netdev, char *addr)
{
	struct enic *enic = netdev_priv(netdev);

	if (enic_is_dynamic(enic) || enic_is_sriov_vf(enic)) {
		if (!is_valid_ether_addr(addr) && !is_zero_ether_addr(addr))
			return -EADDRNOTAVAIL;
	} else {
		if (!is_valid_ether_addr(addr))
			return -EADDRNOTAVAIL;
	}

	memcpy(netdev->dev_addr, addr, netdev->addr_len);

	return 0;
}