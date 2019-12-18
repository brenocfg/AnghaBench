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
struct net_device {int dummy; } ;
struct igb_adapter {int flags; int /*<<< orphan*/  rss_queues; } ;
struct ethtool_channels {int /*<<< orphan*/  combined_count; void* other_count; void* max_other; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 int IGB_FLAG_HAS_MSIX ; 
 void* NON_Q_VECTORS ; 
 int /*<<< orphan*/  igb_max_channels (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void igb_get_channels(struct net_device *netdev,
			     struct ethtool_channels *ch)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	/* Report maximum channels */
	ch->max_combined = igb_max_channels(adapter);

	/* Report info for other vector */
	if (adapter->flags & IGB_FLAG_HAS_MSIX) {
		ch->max_other = NON_Q_VECTORS;
		ch->other_count = NON_Q_VECTORS;
	}

	ch->combined_count = adapter->rss_queues;
}