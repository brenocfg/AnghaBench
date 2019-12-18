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
struct TYPE_4__ {int adaptive_rx; } ;
struct sge_eth_rxq {TYPE_2__ rspq; } ;
struct port_info {size_t first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct sge_eth_rxq* ethrxq; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int get_adaptive_rx_setting(struct net_device *dev)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;
	struct sge_eth_rxq *q = &adap->sge.ethrxq[pi->first_qset];

	return q->rspq.adaptive_rx;
}