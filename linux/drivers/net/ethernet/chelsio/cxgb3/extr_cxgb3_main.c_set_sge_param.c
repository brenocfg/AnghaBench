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
struct qset_params {scalar_t__ rspq_size; scalar_t__ fl_size; scalar_t__ jumbo_size; int* txq_size; } ;
struct port_info {size_t first_qset; int nqsets; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ rx_jumbo_pending; int tx_pending; scalar_t__ rx_mini_pending; } ;
struct TYPE_3__ {struct qset_params* qset; } ;
struct TYPE_4__ {int nports; TYPE_1__ sge; } ;
struct adapter {int flags; TYPE_2__ params; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FULL_INIT_DONE ; 
 scalar_t__ MAX_RSPQ_ENTRIES ; 
 scalar_t__ MAX_RX_BUFFERS ; 
 scalar_t__ MAX_RX_JUMBO_BUFFERS ; 
 int MAX_TXQ_ENTRIES ; 
 scalar_t__ MIN_FL_ENTRIES ; 
 scalar_t__ MIN_RSPQ_ENTRIES ; 
 int MIN_TXQ_ENTRIES ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_sge_param(struct net_device *dev, struct ethtool_ringparam *e)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct qset_params *q;
	int i;

	if (e->rx_pending > MAX_RX_BUFFERS ||
	    e->rx_jumbo_pending > MAX_RX_JUMBO_BUFFERS ||
	    e->tx_pending > MAX_TXQ_ENTRIES ||
	    e->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    e->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES ||
	    e->rx_jumbo_pending < MIN_FL_ENTRIES ||
	    e->tx_pending < adapter->params.nports * MIN_TXQ_ENTRIES)
		return -EINVAL;

	if (adapter->flags & FULL_INIT_DONE)
		return -EBUSY;

	q = &adapter->params.sge.qset[pi->first_qset];
	for (i = 0; i < pi->nqsets; ++i, ++q) {
		q->rspq_size = e->rx_mini_pending;
		q->fl_size = e->rx_pending;
		q->jumbo_size = e->rx_jumbo_pending;
		q->txq_size[0] = e->tx_pending;
		q->txq_size[1] = e->tx_pending;
		q->txq_size[2] = e->tx_pending;
	}
	return 0;
}