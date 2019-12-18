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
struct sge_uld_txq_info {struct sge_uld_txq* uldtxq; } ;
struct sge_uld_txq {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct sge_uld_txq_info** uld_txq_info; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 size_t CXGB4_TX_OFLD ; 
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int net_xmit_eval (int) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int ofld_xmit_direct (struct sge_uld_txq*,void const*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

int cxgb4_immdata_send(struct net_device *dev, unsigned int idx,
		       const void *src, unsigned int len)
{
	struct sge_uld_txq_info *txq_info;
	struct sge_uld_txq *txq;
	struct adapter *adap;
	int ret;

	adap = netdev2adap(dev);

	local_bh_disable();
	txq_info = adap->sge.uld_txq_info[CXGB4_TX_OFLD];
	if (unlikely(!txq_info)) {
		WARN_ON(true);
		local_bh_enable();
		return NET_XMIT_DROP;
	}
	txq = &txq_info->uldtxq[idx];

	ret = ofld_xmit_direct(txq, src, len);
	local_bh_enable();
	return net_xmit_eval(ret);
}