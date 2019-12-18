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
struct sk_buff {int dummy; } ;
struct sge_uld_txq_info {struct sge_uld_txq* uldtxq; } ;
struct sge_uld_txq {int dummy; } ;
struct TYPE_4__ {struct sge_uld_txq_info** uld_txq_info; int /*<<< orphan*/ * ctrlq; } ;
struct TYPE_3__ {scalar_t__ nsftids; } ;
struct adapter {TYPE_2__ sge; TYPE_1__ tids; } ;

/* Variables and functions */
 int NET_XMIT_DROP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ctrl_xmit (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int is_ctrl_pkt (struct sk_buff*) ; 
 int ofld_xmit (struct sge_uld_txq*,struct sk_buff*) ; 
 unsigned int skb_txq (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int uld_send(struct adapter *adap, struct sk_buff *skb,
			   unsigned int tx_uld_type)
{
	struct sge_uld_txq_info *txq_info;
	struct sge_uld_txq *txq;
	unsigned int idx = skb_txq(skb);

	if (unlikely(is_ctrl_pkt(skb))) {
		/* Single ctrl queue is a requirement for LE workaround path */
		if (adap->tids.nsftids)
			idx = 0;
		return ctrl_xmit(&adap->sge.ctrlq[idx], skb);
	}

	txq_info = adap->sge.uld_txq_info[tx_uld_type];
	if (unlikely(!txq_info)) {
		WARN_ON(true);
		return NET_XMIT_DROP;
	}

	txq = &txq_info->uldtxq[idx];
	return ofld_xmit(txq, skb);
}