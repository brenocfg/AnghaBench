#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tcphdr {int doff; int /*<<< orphan*/  seq; } ;
struct sk_buff {int data; scalar_t__ len; struct sk_buff* next; int /*<<< orphan*/ * cb; } ;
struct nes_vnic {int /*<<< orphan*/  nesdev; } ;
struct nes_rskb_cb {scalar_t__ seqnum; } ;
struct TYPE_6__ {struct sk_buff* next; } ;
struct nes_qp {scalar_t__ pau_rcv_nxt; int pau_busy; int pau_pending; scalar_t__ pau_state; int /*<<< orphan*/  pau_lock; TYPE_2__ pau_list; int /*<<< orphan*/  cm_node; TYPE_1__* nesqp_context; } ;
struct iphdr {int ihl; int /*<<< orphan*/  tot_len; } ;
struct TYPE_5__ {int /*<<< orphan*/  rcv_wnd; } ;

/* Variables and functions */
 scalar_t__ PAU_READY ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ before (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  between (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_mgt_free_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_rem_ref_cm_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_fpdus (struct nes_vnic*,struct nes_qp*) ; 
 int /*<<< orphan*/  skb_insert (struct sk_buff*,struct sk_buff*,TYPE_2__*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned char*) ; 
 int /*<<< orphan*/  skb_queue_head (TYPE_2__*,struct sk_buff*) ; 
 scalar_t__ skb_queue_len (TYPE_2__*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_fpdus(struct sk_buff *skb, struct nes_vnic *nesvnic, struct nes_qp *nesqp)
{
	struct sk_buff *tmpskb;
	struct nes_rskb_cb *cb;
	struct iphdr *iph;
	struct tcphdr *tcph;
	unsigned char *tcph_end;
	u32 rcv_nxt;
	u32 rcv_wnd;
	u32 seqnum;
	u32 len;
	bool process_it = false;
	unsigned long flags;

	/* Move data ptr to after tcp header */
	iph = (struct iphdr *)skb->data;
	tcph = (struct tcphdr *)(((char *)iph) + (4 * iph->ihl));
	seqnum = be32_to_cpu(tcph->seq);
	tcph_end = (((char *)tcph) + (4 * tcph->doff));

	len = be16_to_cpu(iph->tot_len);
	if (skb->len > len)
		skb_trim(skb, len);
	skb_pull(skb, tcph_end - skb->data);

	/* Initialize tracking values */
	cb = (struct nes_rskb_cb *)&skb->cb[0];
	cb->seqnum = seqnum;

	/* Make sure data is in the receive window */
	rcv_nxt = nesqp->pau_rcv_nxt;
	rcv_wnd = le32_to_cpu(nesqp->nesqp_context->rcv_wnd);
	if (!between(seqnum, rcv_nxt, (rcv_nxt + rcv_wnd))) {
		nes_mgt_free_skb(nesvnic->nesdev, skb, PCI_DMA_TODEVICE);
		nes_rem_ref_cm_node(nesqp->cm_node);
		return;
	}

	spin_lock_irqsave(&nesqp->pau_lock, flags);

	if (nesqp->pau_busy)
		nesqp->pau_pending = 1;
	else
		nesqp->pau_busy = 1;

	/* Queue skb by sequence number */
	if (skb_queue_len(&nesqp->pau_list) == 0) {
		skb_queue_head(&nesqp->pau_list, skb);
	} else {
		tmpskb = nesqp->pau_list.next;
		while (tmpskb != (struct sk_buff *)&nesqp->pau_list) {
			cb = (struct nes_rskb_cb *)&tmpskb->cb[0];
			if (before(seqnum, cb->seqnum))
				break;
			tmpskb = tmpskb->next;
		}
		skb_insert(tmpskb, skb, &nesqp->pau_list);
	}
	if (nesqp->pau_state == PAU_READY)
		process_it = true;
	spin_unlock_irqrestore(&nesqp->pau_lock, flags);

	if (process_it)
		process_fpdus(nesvnic, nesqp);

	return;
}