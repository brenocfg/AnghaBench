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
typedef  int u16 ;
struct ixgbe_ring_feature {int limit; int indices; int /*<<< orphan*/  mask; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {int flags; int num_rx_queues; int num_tx_queues; int /*<<< orphan*/  num_xdp_queues; struct ixgbe_ring_feature* ring_feature; scalar_t__ atr_sample_rate; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int IXGBE_FLAG_FDIR_HASH_CAPABLE ; 
 int IXGBE_FLAG_FDIR_PERFECT_CAPABLE ; 
 int /*<<< orphan*/  IXGBE_RSS_16Q_MASK ; 
 int /*<<< orphan*/  IXGBE_RSS_64Q_MASK ; 
 size_t RING_F_FDIR ; 
 size_t RING_F_RSS ; 
 scalar_t__ ixgbe_mac_X550 ; 
 int /*<<< orphan*/  ixgbe_xdp_queues (struct ixgbe_adapter*) ; 

__attribute__((used)) static bool ixgbe_set_rss_queues(struct ixgbe_adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	struct ixgbe_ring_feature *f;
	u16 rss_i;

	/* set mask for 16 queue limit of RSS */
	f = &adapter->ring_feature[RING_F_RSS];
	rss_i = f->limit;

	f->indices = rss_i;

	if (hw->mac.type < ixgbe_mac_X550)
		f->mask = IXGBE_RSS_16Q_MASK;
	else
		f->mask = IXGBE_RSS_64Q_MASK;

	/* disable ATR by default, it will be configured below */
	adapter->flags &= ~IXGBE_FLAG_FDIR_HASH_CAPABLE;

	/*
	 * Use Flow Director in addition to RSS to ensure the best
	 * distribution of flows across cores, even when an FDIR flow
	 * isn't matched.
	 */
	if (rss_i > 1 && adapter->atr_sample_rate) {
		f = &adapter->ring_feature[RING_F_FDIR];

		rss_i = f->indices = f->limit;

		if (!(adapter->flags & IXGBE_FLAG_FDIR_PERFECT_CAPABLE))
			adapter->flags |= IXGBE_FLAG_FDIR_HASH_CAPABLE;
	}

#ifdef IXGBE_FCOE
	/*
	 * FCoE can exist on the same rings as standard network traffic
	 * however it is preferred to avoid that if possible.  In order
	 * to get the best performance we allocate as many FCoE queues
	 * as we can and we place them at the end of the ring array to
	 * avoid sharing queues with standard RSS on systems with 24 or
	 * more CPUs.
	 */
	if (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) {
		struct net_device *dev = adapter->netdev;
		u16 fcoe_i;

		f = &adapter->ring_feature[RING_F_FCOE];

		/* merge FCoE queues with RSS queues */
		fcoe_i = min_t(u16, f->limit + rss_i, num_online_cpus());
		fcoe_i = min_t(u16, fcoe_i, dev->num_tx_queues);

		/* limit indices to rss_i if MSI-X is disabled */
		if (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED))
			fcoe_i = rss_i;

		/* attempt to reserve some queues for just FCoE */
		f->indices = min_t(u16, fcoe_i, f->limit);
		f->offset = fcoe_i - f->indices;
		rss_i = max_t(u16, fcoe_i, rss_i);
	}

#endif /* IXGBE_FCOE */
	adapter->num_rx_queues = rss_i;
	adapter->num_tx_queues = rss_i;
	adapter->num_xdp_queues = ixgbe_xdp_queues(adapter);

	return true;
}