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
struct sge_eth_rxq {int /*<<< orphan*/  rspq; } ;
struct port_info {size_t first_qset; int nqsets; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct sge_eth_rxq* ethrxq; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int cxgb4_set_rspq_intr_params (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_rx_intr_params(struct net_device *dev,
			      unsigned int us, unsigned int cnt)
{
	int i, err;
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adap = pi->adapter;
	struct sge_eth_rxq *q = &adap->sge.ethrxq[pi->first_qset];

	for (i = 0; i < pi->nqsets; i++, q++) {
		err = cxgb4_set_rspq_intr_params(&q->rspq, us, cnt);
		if (err)
			return err;
	}
	return 0;
}