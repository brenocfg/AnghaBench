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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct ixgbe_q_vector {int itr; TYPE_2__ rx; TYPE_1__ tx; } ;
struct ixgbe_adapter {int rx_itr_setting; int tx_itr_setting; int num_q_vectors; struct ixgbe_q_vector** q_vector; } ;
struct ethtool_coalesce {int tx_coalesce_usecs; int rx_coalesce_usecs; } ;

/* Variables and functions */
 int EINVAL ; 
 int IXGBE_100K_ITR ; 
 int IXGBE_12K_ITR ; 
 int IXGBE_20K_ITR ; 
 int IXGBE_MAX_EITR ; 
 int /*<<< orphan*/  ixgbe_do_reset (struct net_device*) ; 
 int ixgbe_update_rsc (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_write_eitr (struct ixgbe_q_vector*) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_set_coalesce(struct net_device *netdev,
			      struct ethtool_coalesce *ec)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_q_vector *q_vector;
	int i;
	u16 tx_itr_param, rx_itr_param, tx_itr_prev;
	bool need_reset = false;

	if (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count) {
		/* reject Tx specific changes in case of mixed RxTx vectors */
		if (ec->tx_coalesce_usecs)
			return -EINVAL;
		tx_itr_prev = adapter->rx_itr_setting;
	} else {
		tx_itr_prev = adapter->tx_itr_setting;
	}

	if ((ec->rx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)) ||
	    (ec->tx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)))
		return -EINVAL;

	if (ec->rx_coalesce_usecs > 1)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;
	else
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;

	if (adapter->rx_itr_setting == 1)
		rx_itr_param = IXGBE_20K_ITR;
	else
		rx_itr_param = adapter->rx_itr_setting;

	if (ec->tx_coalesce_usecs > 1)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;
	else
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;

	if (adapter->tx_itr_setting == 1)
		tx_itr_param = IXGBE_12K_ITR;
	else
		tx_itr_param = adapter->tx_itr_setting;

	/* mixed Rx/Tx */
	if (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count)
		adapter->tx_itr_setting = adapter->rx_itr_setting;

	/* detect ITR changes that require update of TXDCTL.WTHRESH */
	if ((adapter->tx_itr_setting != 1) &&
	    (adapter->tx_itr_setting < IXGBE_100K_ITR)) {
		if ((tx_itr_prev == 1) ||
		    (tx_itr_prev >= IXGBE_100K_ITR))
			need_reset = true;
	} else {
		if ((tx_itr_prev != 1) &&
		    (tx_itr_prev < IXGBE_100K_ITR))
			need_reset = true;
	}

	/* check the old value and enable RSC if necessary */
	need_reset |= ixgbe_update_rsc(adapter);

	for (i = 0; i < adapter->num_q_vectors; i++) {
		q_vector = adapter->q_vector[i];
		if (q_vector->tx.count && !q_vector->rx.count)
			/* tx only */
			q_vector->itr = tx_itr_param;
		else
			/* rx only or mixed */
			q_vector->itr = rx_itr_param;
		ixgbe_write_eitr(q_vector);
	}

	/*
	 * do reset here at the end to make sure EITR==0 case is handled
	 * correctly w.r.t stopping tx, and changing TXDCTL.WTHRESH settings
	 * also locks in RSC enable/disable which requires reset
	 */
	if (need_reset)
		ixgbe_do_reset(netdev);

	return 0;
}