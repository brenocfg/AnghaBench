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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbevf_adapter {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBEVF_82599_RETA_SIZE ; 
 int /*<<< orphan*/  IXGBEVF_X550_VFRETA_SIZE ; 
 scalar_t__ ixgbe_mac_X550_vf ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 ixgbevf_get_rxfh_indir_size(struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);

	if (adapter->hw.mac.type >= ixgbe_mac_X550_vf)
		return IXGBEVF_X550_VFRETA_SIZE;

	return IXGBEVF_82599_RETA_SIZE;
}