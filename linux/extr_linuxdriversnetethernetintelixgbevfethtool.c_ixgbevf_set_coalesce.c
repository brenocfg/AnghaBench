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
typedef  void* u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ count; } ;
struct ixgbevf_q_vector {void* itr; TYPE_2__ rx; TYPE_1__ tx; } ;
struct ixgbevf_adapter {int rx_itr_setting; int tx_itr_setting; int num_msix_vectors; struct ixgbevf_q_vector** q_vector; } ;
struct ethtool_coalesce {int tx_coalesce_usecs; int rx_coalesce_usecs; } ;

/* Variables and functions */
 int EINVAL ; 
 void* IXGBE_12K_ITR ; 
 void* IXGBE_20K_ITR ; 
 int IXGBE_MAX_EITR ; 
 int NON_Q_VECTORS ; 
 int /*<<< orphan*/  ixgbevf_write_eitr (struct ixgbevf_q_vector*) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbevf_set_coalesce(struct net_device *netdev,
				struct ethtool_coalesce *ec)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct ixgbevf_q_vector *q_vector;
	int num_vectors, i;
	u16 tx_itr_param, rx_itr_param;

	/* don't accept Tx specific changes if we've got mixed RxTx vectors */
	if (adapter->q_vector[0]->tx.count &&
	    adapter->q_vector[0]->rx.count && ec->tx_coalesce_usecs)
		return -EINVAL;

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

	num_vectors = adapter->num_msix_vectors - NON_Q_VECTORS;

	for (i = 0; i < num_vectors; i++) {
		q_vector = adapter->q_vector[i];
		if (q_vector->tx.count && !q_vector->rx.count)
			/* Tx only */
			q_vector->itr = tx_itr_param;
		else
			/* Rx only or mixed */
			q_vector->itr = rx_itr_param;
		ixgbevf_write_eitr(q_vector);
	}

	return 0;
}