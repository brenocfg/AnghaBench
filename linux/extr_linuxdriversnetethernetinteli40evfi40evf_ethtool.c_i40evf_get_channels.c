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
struct i40evf_adapter {int /*<<< orphan*/  num_active_queues; } ;
struct ethtool_channels {int /*<<< orphan*/  combined_count; void* other_count; void* max_other; int /*<<< orphan*/  max_combined; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40EVF_MAX_REQ_QUEUES ; 
 void* NONQ_VECS ; 
 struct i40evf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void i40evf_get_channels(struct net_device *netdev,
				struct ethtool_channels *ch)
{
	struct i40evf_adapter *adapter = netdev_priv(netdev);

	/* Report maximum channels */
	ch->max_combined = I40EVF_MAX_REQ_QUEUES;

	ch->max_other = NONQ_VECS;
	ch->other_count = NONQ_VECS;

	ch->combined_count = adapter->num_active_queues;
}