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
struct net_device {int features; } ;
struct ixgbe_adapter {int flags2; int rx_itr_setting; struct net_device* netdev; } ;

/* Variables and functions */
 int IXGBE_FLAG2_RSC_CAPABLE ; 
 int IXGBE_FLAG2_RSC_ENABLED ; 
 int IXGBE_MIN_RSC_ITR ; 
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static bool ixgbe_update_rsc(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	/* nothing to do if LRO or RSC are not enabled */
	if (!(adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE) ||
	    !(netdev->features & NETIF_F_LRO))
		return false;

	/* check the feature flag value and enable RSC if necessary */
	if (adapter->rx_itr_setting == 1 ||
	    adapter->rx_itr_setting > IXGBE_MIN_RSC_ITR) {
		if (!(adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)) {
			adapter->flags2 |= IXGBE_FLAG2_RSC_ENABLED;
			e_info(probe, "rx-usecs value high enough to re-enable RSC\n");
			return true;
		}
	/* if interrupt rate is too high then disable RSC */
	} else if (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED) {
		adapter->flags2 &= ~IXGBE_FLAG2_RSC_ENABLED;
		e_info(probe, "rx-usecs set too low, disabling RSC\n");
		return true;
	}
	return false;
}