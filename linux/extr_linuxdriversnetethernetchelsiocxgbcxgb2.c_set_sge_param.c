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
struct net_device {struct adapter* ml_priv; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ rx_jumbo_pending; int tx_pending; scalar_t__ rx_mini_pending; } ;
struct TYPE_3__ {scalar_t__* freelQ_size; int* cmdQ_size; } ;
struct TYPE_4__ {int nports; TYPE_1__ sge; } ;
struct adapter {int flags; TYPE_2__ params; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FULL_INIT_DONE ; 
 int MAX_CMDQ1_ENTRIES ; 
 int MAX_CMDQ_ENTRIES ; 
 scalar_t__ MAX_RX_BUFFERS ; 
 scalar_t__ MAX_RX_JUMBO_BUFFERS ; 
 int MAX_SKB_FRAGS ; 
 scalar_t__ MIN_FL_ENTRIES ; 
 scalar_t__ t1_is_T1B (struct adapter*) ; 

__attribute__((used)) static int set_sge_param(struct net_device *dev, struct ethtool_ringparam *e)
{
	struct adapter *adapter = dev->ml_priv;
	int jumbo_fl = t1_is_T1B(adapter) ? 1 : 0;

	if (e->rx_pending > MAX_RX_BUFFERS || e->rx_mini_pending ||
	    e->rx_jumbo_pending > MAX_RX_JUMBO_BUFFERS ||
	    e->tx_pending > MAX_CMDQ_ENTRIES ||
	    e->rx_pending < MIN_FL_ENTRIES ||
	    e->rx_jumbo_pending < MIN_FL_ENTRIES ||
	    e->tx_pending < (adapter->params.nports + 1) * (MAX_SKB_FRAGS + 1))
		return -EINVAL;

	if (adapter->flags & FULL_INIT_DONE)
		return -EBUSY;

	adapter->params.sge.freelQ_size[!jumbo_fl] = e->rx_pending;
	adapter->params.sge.freelQ_size[jumbo_fl] = e->rx_jumbo_pending;
	adapter->params.sge.cmdQ_size[0] = e->tx_pending;
	adapter->params.sge.cmdQ_size[1] = e->tx_pending > MAX_CMDQ1_ENTRIES ?
		MAX_CMDQ1_ENTRIES : e->tx_pending;
	return 0;
}