#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sge {TYPE_5__* ethrxq; TYPE_2__* ethtxq; } ;
struct port_info {int nqsets; int first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_pending; } ;
struct adapter {int flags; struct sge sge; } ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_4__ rspq; TYPE_3__ fl; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_7__ {TYPE_1__ q; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FULL_INIT_DONE ; 
 scalar_t__ MAX_RSPQ_ENTRIES ; 
 scalar_t__ MAX_RX_BUFFERS ; 
 scalar_t__ MAX_TXQ_ENTRIES ; 
 scalar_t__ MIN_FL_ENTRIES ; 
 scalar_t__ MIN_RSPQ_ENTRIES ; 
 scalar_t__ MIN_TXQ_ENTRIES ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_sge_param(struct net_device *dev, struct ethtool_ringparam *e)
{
	int i;
	const struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct sge *s = &adapter->sge;

	if (e->rx_pending > MAX_RX_BUFFERS || e->rx_jumbo_pending ||
	    e->tx_pending > MAX_TXQ_ENTRIES ||
	    e->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    e->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES || e->tx_pending < MIN_TXQ_ENTRIES)
		return -EINVAL;

	if (adapter->flags & FULL_INIT_DONE)
		return -EBUSY;

	for (i = 0; i < pi->nqsets; ++i) {
		s->ethtxq[pi->first_qset + i].q.size = e->tx_pending;
		s->ethrxq[pi->first_qset + i].fl.size = e->rx_pending + 8;
		s->ethrxq[pi->first_qset + i].rspq.size = e->rx_mini_pending;
	}
	return 0;
}