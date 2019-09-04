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
struct net_device {int flags; } ;
struct be_adapter {int /*<<< orphan*/  rx_filter_lock; struct net_device* netdev; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 scalar_t__ be_in_all_promisc (struct be_adapter*) ; 
 int /*<<< orphan*/  be_set_all_promisc (struct be_adapter*) ; 
 int /*<<< orphan*/  be_set_mc_list (struct be_adapter*) ; 
 int /*<<< orphan*/  be_set_uc_list (struct be_adapter*) ; 
 int /*<<< orphan*/  be_vid_config (struct be_adapter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __be_set_rx_mode(struct be_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	mutex_lock(&adapter->rx_filter_lock);

	if (netdev->flags & IFF_PROMISC) {
		if (!be_in_all_promisc(adapter))
			be_set_all_promisc(adapter);
	} else if (be_in_all_promisc(adapter)) {
		/* We need to re-program the vlan-list or clear
		 * vlan-promisc mode (if needed) when the interface
		 * comes out of promisc mode.
		 */
		be_vid_config(adapter);
	}

	be_set_uc_list(adapter);
	be_set_mc_list(adapter);

	mutex_unlock(&adapter->rx_filter_lock);
}