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
struct sge_uld_txq_info {struct sge_uld_txq* uldtxq; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sge_uld_txq {TYPE_1__ sendq; scalar_t__ full; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct sge_uld_txq_info** uld_txq_info; } ;
struct adapter {TYPE_2__ sge; } ;

/* Variables and functions */
 size_t CXGB4_TX_CRYPTO ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cxgb4_is_crypto_q_full(struct net_device *dev, unsigned int idx)
{
	struct adapter *adap = netdev2adap(dev);
	struct sge_uld_txq_info *txq_info =
		adap->sge.uld_txq_info[CXGB4_TX_CRYPTO];
	struct sge_uld_txq *txq;
	int ret = 0;

	local_bh_disable();
	txq = &txq_info->uldtxq[idx];
	spin_lock(&txq->sendq.lock);
	if (txq->full)
		ret = -1;
	spin_unlock(&txq->sendq.lock);
	local_bh_enable();
	return ret;
}