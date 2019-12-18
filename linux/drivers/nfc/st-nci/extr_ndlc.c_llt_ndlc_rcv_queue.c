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
typedef  int u8 ;
struct sk_buff {int* data; } ;
struct TYPE_2__ {scalar_t__ qlen; } ;
struct llt_ndlc {int t2_active; int t1_active; int /*<<< orphan*/  ndev; int /*<<< orphan*/  t1_timer; int /*<<< orphan*/  t2_timer; TYPE_1__ ack_pending_q; TYPE_1__ rcv_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDLC_TIMER_T1 ; 
 int /*<<< orphan*/  NDLC_TIMER_T1_WAIT ; 
#define  PCB_SYNC_ACK 130 
 int PCB_SYNC_MASK ; 
#define  PCB_SYNC_NACK 129 
#define  PCB_SYNC_WAIT 128 
 int PCB_TYPE_DATAFRAME ; 
 int PCB_TYPE_MASK ; 
 int PCB_TYPE_SUPERVISOR ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  llt_ndlc_requeue_data_pending (struct llt_ndlc*) ; 
 int /*<<< orphan*/  llt_ndlc_send_queue (struct llt_ndlc*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_recv_frame (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 struct sk_buff* skb_dequeue (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void llt_ndlc_rcv_queue(struct llt_ndlc *ndlc)
{
	struct sk_buff *skb;
	u8 pcb;
	unsigned long time_sent;

	if (ndlc->rcv_q.qlen)
		pr_debug("rcvQlen=%d\n", ndlc->rcv_q.qlen);

	while ((skb = skb_dequeue(&ndlc->rcv_q)) != NULL) {
		pcb = skb->data[0];
		skb_pull(skb, 1);
		if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_SUPERVISOR) {
			switch (pcb & PCB_SYNC_MASK) {
			case PCB_SYNC_ACK:
				skb = skb_dequeue(&ndlc->ack_pending_q);
				kfree_skb(skb);
				del_timer_sync(&ndlc->t1_timer);
				del_timer_sync(&ndlc->t2_timer);
				ndlc->t2_active = false;
				ndlc->t1_active = false;
				break;
			case PCB_SYNC_NACK:
				llt_ndlc_requeue_data_pending(ndlc);
				llt_ndlc_send_queue(ndlc);
				/* start timer t1 for ndlc aknowledge */
				time_sent = jiffies;
				ndlc->t1_active = true;
				mod_timer(&ndlc->t1_timer, time_sent +
					msecs_to_jiffies(NDLC_TIMER_T1));
				break;
			case PCB_SYNC_WAIT:
				time_sent = jiffies;
				ndlc->t1_active = true;
				mod_timer(&ndlc->t1_timer, time_sent +
					  msecs_to_jiffies(NDLC_TIMER_T1_WAIT));
				break;
			default:
				kfree_skb(skb);
				break;
			}
		} else if ((pcb & PCB_TYPE_MASK) == PCB_TYPE_DATAFRAME) {
			nci_recv_frame(ndlc->ndev, skb);
		} else {
			kfree_skb(skb);
		}
	}
}