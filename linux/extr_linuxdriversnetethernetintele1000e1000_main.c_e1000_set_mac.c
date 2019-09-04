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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct e1000_hw {scalar_t__ mac_type; int /*<<< orphan*/  mac_addr; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ e1000_82542_rev2_0 ; 
 int /*<<< orphan*/  e1000_enter_82542_rst (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_leave_82542_rst (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_rar_set (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int e1000_set_mac(struct net_device *netdev, void *p)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* 82542 2.0 needs to be in reset to write receive address registers */

	if (hw->mac_type == e1000_82542_rev2_0)
		e1000_enter_82542_rst(adapter);

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	memcpy(hw->mac_addr, addr->sa_data, netdev->addr_len);

	e1000_rar_set(hw, hw->mac_addr, 0);

	if (hw->mac_type == e1000_82542_rev2_0)
		e1000_leave_82542_rst(adapter);

	return 0;
}