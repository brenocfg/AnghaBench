#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sge_qset {int dummy; } ;
struct qset_params {int coalesce_usecs; } ;
struct port_info {int nqsets; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; } ;
struct TYPE_6__ {struct sge_qset* qs; } ;
struct TYPE_4__ {struct qset_params* qset; } ;
struct TYPE_5__ {TYPE_1__ sge; } ;
struct adapter {TYPE_3__ sge; TYPE_2__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_NEWTIMER ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  t3_update_qset_coalesce (struct sge_qset*,struct qset_params*) ; 

__attribute__((used)) static int set_coalesce(struct net_device *dev, struct ethtool_coalesce *c)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	struct qset_params *qsp;
	struct sge_qset *qs;
	int i;

	if (c->rx_coalesce_usecs * 10 > M_NEWTIMER)
		return -EINVAL;

	for (i = 0; i < pi->nqsets; i++) {
		qsp = &adapter->params.sge.qset[i];
		qs = &adapter->sge.qs[i];
		qsp->coalesce_usecs = c->rx_coalesce_usecs;
		t3_update_qset_coalesce(qs, qsp);
	}

	return 0;
}