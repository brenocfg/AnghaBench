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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags; } ;

/* Variables and functions */
 int IXGBE_FLAG_DCB_ENABLED ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 ixgbe_dcbnl_get_state(struct net_device *netdev)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	return !!(adapter->flags & IXGBE_FLAG_DCB_ENABLED);
}