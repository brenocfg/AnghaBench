#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sge {TYPE_6__* ethtxq; TYPE_4__* ethrxq; } ;
struct port_info {size_t first_qset; TYPE_1__* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; scalar_t__ rx_jumbo_pending; int /*<<< orphan*/  rx_mini_pending; scalar_t__ rx_pending; int /*<<< orphan*/  tx_max_pending; scalar_t__ rx_jumbo_max_pending; int /*<<< orphan*/  rx_mini_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_11__ {int /*<<< orphan*/  size; } ;
struct TYPE_12__ {TYPE_5__ q; } ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_3__ rspq; TYPE_2__ fl; } ;
struct TYPE_7__ {struct sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_RSPQ_ENTRIES ; 
 int /*<<< orphan*/  MAX_RX_BUFFERS ; 
 int /*<<< orphan*/  MAX_TXQ_ENTRIES ; 
 scalar_t__ MIN_FL_RESID ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void cxgb4vf_get_ringparam(struct net_device *dev,
				  struct ethtool_ringparam *rp)
{
	const struct port_info *pi = netdev_priv(dev);
	const struct sge *s = &pi->adapter->sge;

	rp->rx_max_pending = MAX_RX_BUFFERS;
	rp->rx_mini_max_pending = MAX_RSPQ_ENTRIES;
	rp->rx_jumbo_max_pending = 0;
	rp->tx_max_pending = MAX_TXQ_ENTRIES;

	rp->rx_pending = s->ethrxq[pi->first_qset].fl.size - MIN_FL_RESID;
	rp->rx_mini_pending = s->ethrxq[pi->first_qset].rspq.size;
	rp->rx_jumbo_pending = 0;
	rp->tx_pending = s->ethtxq[pi->first_qset].q.size;
}