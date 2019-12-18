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
struct sge {TYPE_5__* ethtxq; TYPE_3__* ethrxq; } ;
struct port_info {int first_qset; int nqsets; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; scalar_t__ rx_mini_pending; scalar_t__ rx_jumbo_pending; } ;
struct adapter {int flags; struct sge sge; } ;
struct TYPE_9__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_4__ q; } ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_8__ {TYPE_2__ rspq; TYPE_1__ fl; } ;

/* Variables and functions */
 int CXGB4VF_FULL_INIT_DONE ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ MAX_RSPQ_ENTRIES ; 
 scalar_t__ MAX_RX_BUFFERS ; 
 scalar_t__ MAX_TXQ_ENTRIES ; 
 scalar_t__ MIN_FL_ENTRIES ; 
 scalar_t__ MIN_FL_RESID ; 
 scalar_t__ MIN_RSPQ_ENTRIES ; 
 scalar_t__ MIN_TXQ_ENTRIES ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int cxgb4vf_set_ringparam(struct net_device *dev,
				 struct ethtool_ringparam *rp)
{
	const struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct sge *s = &adapter->sge;
	int qs;

	if (rp->rx_pending > MAX_RX_BUFFERS ||
	    rp->rx_jumbo_pending ||
	    rp->tx_pending > MAX_TXQ_ENTRIES ||
	    rp->rx_mini_pending > MAX_RSPQ_ENTRIES ||
	    rp->rx_mini_pending < MIN_RSPQ_ENTRIES ||
	    rp->rx_pending < MIN_FL_ENTRIES ||
	    rp->tx_pending < MIN_TXQ_ENTRIES)
		return -EINVAL;

	if (adapter->flags & CXGB4VF_FULL_INIT_DONE)
		return -EBUSY;

	for (qs = pi->first_qset; qs < pi->first_qset + pi->nqsets; qs++) {
		s->ethrxq[qs].fl.size = rp->rx_pending + MIN_FL_RESID;
		s->ethrxq[qs].rspq.size = rp->rx_mini_pending;
		s->ethtxq[qs].q.size = rp->tx_pending;
	}
	return 0;
}