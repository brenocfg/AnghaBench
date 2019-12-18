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
struct net_device {int addr_assign_type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct alx_hw {int /*<<< orphan*/  mac_addr; } ;
struct alx_priv {struct alx_hw hw; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int NET_ADDR_RANDOM ; 
 int /*<<< orphan*/  alx_set_macaddr (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alx_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int alx_set_mac_address(struct net_device *netdev, void *data)
{
	struct alx_priv *alx = netdev_priv(netdev);
	struct alx_hw *hw = &alx->hw;
	struct sockaddr *addr = data;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	if (netdev->addr_assign_type & NET_ADDR_RANDOM)
		netdev->addr_assign_type ^= NET_ADDR_RANDOM;

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	memcpy(hw->mac_addr, addr->sa_data, netdev->addr_len);
	alx_set_macaddr(hw, hw->mac_addr);

	return 0;
}