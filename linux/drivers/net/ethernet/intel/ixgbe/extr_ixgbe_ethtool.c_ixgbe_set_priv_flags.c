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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {unsigned int flags2; } ;

/* Variables and functions */
 unsigned int IXGBE_FLAG2_RX_LEGACY ; 
 unsigned int IXGBE_FLAG2_VF_IPSEC_ENABLED ; 
 int IXGBE_PRIV_FLAGS_LEGACY_RX ; 
 int IXGBE_PRIV_FLAGS_VF_IPSEC_EN ; 
 int /*<<< orphan*/  ixgbe_reinit_locked (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_priv_flags(struct net_device *netdev, u32 priv_flags)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	unsigned int flags2 = adapter->flags2;

	flags2 &= ~IXGBE_FLAG2_RX_LEGACY;
	if (priv_flags & IXGBE_PRIV_FLAGS_LEGACY_RX)
		flags2 |= IXGBE_FLAG2_RX_LEGACY;

	flags2 &= ~IXGBE_FLAG2_VF_IPSEC_ENABLED;
	if (priv_flags & IXGBE_PRIV_FLAGS_VF_IPSEC_EN)
		flags2 |= IXGBE_FLAG2_VF_IPSEC_ENABLED;

	if (flags2 != adapter->flags2) {
		adapter->flags2 = flags2;

		/* reset interface to repopulate queues */
		if (netif_running(netdev))
			ixgbe_reinit_locked(adapter);
	}

	return 0;
}