#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags; int hw_tcs; TYPE_1__* ring_feature; int /*<<< orphan*/  atr_sample_rate; } ;
struct ethtool_channels {int combined_count; void* other_count; void* max_other; int /*<<< orphan*/  max_combined; } ;
struct TYPE_2__ {int indices; } ;

/* Variables and functions */
 int IXGBE_FLAG_MSIX_ENABLED ; 
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 void* NON_Q_VECTORS ; 
 size_t RING_F_FDIR ; 
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  ixgbe_max_channels (struct ixgbe_adapter*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_get_channels(struct net_device *dev,
			       struct ethtool_channels *ch)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	/* report maximum channels */
	ch->max_combined = ixgbe_max_channels(adapter);

	/* report info for other vector */
	if (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) {
		ch->max_other = NON_Q_VECTORS;
		ch->other_count = NON_Q_VECTORS;
	}

	/* record RSS queues */
	ch->combined_count = adapter->ring_feature[RING_F_RSS].indices;

	/* nothing else to report if RSS is disabled */
	if (ch->combined_count == 1)
		return;

	/* we do not support ATR queueing if SR-IOV is enabled */
	if (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		return;

	/* same thing goes for being DCB enabled */
	if (adapter->hw_tcs > 1)
		return;

	/* if ATR is disabled we can exit */
	if (!adapter->atr_sample_rate)
		return;

	/* report flow director queues as maximum channels */
	ch->combined_count = adapter->ring_feature[RING_F_FDIR].indices;
}