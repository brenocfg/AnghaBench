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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ixgbevf_adapter {int flags; } ;

/* Variables and functions */
 int IXGBEVF_FLAGS_LEGACY_RX ; 
 int /*<<< orphan*/  IXGBEVF_PRIV_FLAGS_LEGACY_RX ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 ixgbevf_get_priv_flags(struct net_device *netdev)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	if (adapter->flags & IXGBEVF_FLAGS_LEGACY_RX)
		priv_flags |= IXGBEVF_PRIV_FLAGS_LEGACY_RX;

	return priv_flags;
}