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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rar_set ) (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_4__ {scalar_t__ rar_entry_count; int /*<<< orphan*/  addr; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_2__ mac; } ;
struct e1000_adapter {int flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int FLAG_RESET_OVERWRITES_LAA ; 
 int /*<<< orphan*/  e1000e_set_laa_state_82571 (struct e1000_hw*,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int e1000_set_mac(struct net_device *netdev, void *p)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	memcpy(adapter->hw.mac.addr, addr->sa_data, netdev->addr_len);

	hw->mac.ops.rar_set(&adapter->hw, adapter->hw.mac.addr, 0);

	if (adapter->flags & FLAG_RESET_OVERWRITES_LAA) {
		/* activate the work around */
		e1000e_set_laa_state_82571(&adapter->hw, 1);

		/* Hold a copy of the LAA in RAR[14] This is done so that
		 * between the time RAR[0] gets clobbered  and the time it
		 * gets fixed (in e1000_watchdog), the actual LAA is in one
		 * of the RARs and no incoming packets directed to this port
		 * are dropped. Eventually the LAA will be in RAR[0] and
		 * RAR[14]
		 */
		hw->mac.ops.rar_set(&adapter->hw, adapter->hw.mac.addr,
				    adapter->hw.mac.rar_entry_count - 1);
	}

	return 0;
}