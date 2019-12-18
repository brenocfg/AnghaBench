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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  work_limit; } ;
struct igb_q_vector {int itr_val; int set_itr; TYPE_2__ rx; TYPE_1__ tx; } ;
struct igb_adapter {int flags; int rx_itr_setting; int tx_itr_setting; int num_q_vectors; int /*<<< orphan*/  tx_work_limit; struct igb_q_vector** q_vector; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int tx_coalesce_usecs; scalar_t__ rate_sample_interval; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ tx_max_coalesced_frames; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 int IGB_FLAG_DMAC ; 
 int IGB_FLAG_QUEUE_PAIRS ; 
 int IGB_MAX_ITR_USECS ; 
 int IGB_MIN_ITR_USECS ; 
 int IGB_START_ITR ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_set_coalesce(struct net_device *netdev,
			    struct ethtool_coalesce *ec)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	int i;

	if (ec->rx_max_coalesced_frames ||
	    ec->rx_coalesce_usecs_irq ||
	    ec->rx_max_coalesced_frames_irq ||
	    ec->tx_max_coalesced_frames ||
	    ec->tx_coalesce_usecs_irq ||
	    ec->stats_block_coalesce_usecs ||
	    ec->use_adaptive_rx_coalesce ||
	    ec->use_adaptive_tx_coalesce ||
	    ec->pkt_rate_low ||
	    ec->rx_coalesce_usecs_low ||
	    ec->rx_max_coalesced_frames_low ||
	    ec->tx_coalesce_usecs_low ||
	    ec->tx_max_coalesced_frames_low ||
	    ec->pkt_rate_high ||
	    ec->rx_coalesce_usecs_high ||
	    ec->rx_max_coalesced_frames_high ||
	    ec->tx_coalesce_usecs_high ||
	    ec->tx_max_coalesced_frames_high ||
	    ec->rate_sample_interval)
		return -ENOTSUPP;

	if ((ec->rx_coalesce_usecs > IGB_MAX_ITR_USECS) ||
	    ((ec->rx_coalesce_usecs > 3) &&
	     (ec->rx_coalesce_usecs < IGB_MIN_ITR_USECS)) ||
	    (ec->rx_coalesce_usecs == 2))
		return -EINVAL;

	if ((ec->tx_coalesce_usecs > IGB_MAX_ITR_USECS) ||
	    ((ec->tx_coalesce_usecs > 3) &&
	     (ec->tx_coalesce_usecs < IGB_MIN_ITR_USECS)) ||
	    (ec->tx_coalesce_usecs == 2))
		return -EINVAL;

	if ((adapter->flags & IGB_FLAG_QUEUE_PAIRS) && ec->tx_coalesce_usecs)
		return -EINVAL;

	/* If ITR is disabled, disable DMAC */
	if (ec->rx_coalesce_usecs == 0) {
		if (adapter->flags & IGB_FLAG_DMAC)
			adapter->flags &= ~IGB_FLAG_DMAC;
	}

	/* convert to rate of irq's per second */
	if (ec->rx_coalesce_usecs && ec->rx_coalesce_usecs <= 3)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;
	else
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;

	/* convert to rate of irq's per second */
	if (adapter->flags & IGB_FLAG_QUEUE_PAIRS)
		adapter->tx_itr_setting = adapter->rx_itr_setting;
	else if (ec->tx_coalesce_usecs && ec->tx_coalesce_usecs <= 3)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;
	else
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;

	for (i = 0; i < adapter->num_q_vectors; i++) {
		struct igb_q_vector *q_vector = adapter->q_vector[i];
		q_vector->tx.work_limit = adapter->tx_work_limit;
		if (q_vector->rx.ring)
			q_vector->itr_val = adapter->rx_itr_setting;
		else
			q_vector->itr_val = adapter->tx_itr_setting;
		if (q_vector->itr_val && q_vector->itr_val <= 3)
			q_vector->itr_val = IGB_START_ITR;
		q_vector->set_itr = 1;
	}

	return 0;
}