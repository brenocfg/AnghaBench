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
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct TYPE_2__ {int qlen; int /*<<< orphan*/  lock; } ;
struct sge_uld_txq {TYPE_1__ sendq; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  calc_tx_flits_ofld (struct sk_buff*) ; 
 int /*<<< orphan*/  service_ofldq (struct sge_uld_txq*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofld_xmit(struct sge_uld_txq *q, struct sk_buff *skb)
{
	skb->priority = calc_tx_flits_ofld(skb);       /* save for restart */
	spin_lock(&q->sendq.lock);

	/* Queue the new skb onto the Offload Queue's Pending Send Queue.  If
	 * that results in this new skb being the only one on the queue, start
	 * servicing it.  If there are other skbs already on the list, then
	 * either the queue is currently being processed or it's been stopped
	 * for some reason and it'll be restarted at a later time.  Restart
	 * paths are triggered by events like experiencing a DMA Mapping Error
	 * or filling the Hardware TX Ring.
	 */
	__skb_queue_tail(&q->sendq, skb);
	if (q->sendq.qlen == 1)
		service_ofldq(q);

	spin_unlock(&q->sendq.lock);
	return NET_XMIT_SUCCESS;
}