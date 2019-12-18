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
struct sk_buff {scalar_t__ ip_summed; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_qdio_out_buffer {scalar_t__ next_element_to_fill; int /*<<< orphan*/  skb_list; int /*<<< orphan*/  state; struct qeth_qdio_out_q* q; } ;
struct TYPE_2__ {int gso_segs; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ QETH_QDIO_BUF_IN_CQ ; 
 scalar_t__ QETH_QDIO_BUF_PENDING ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_ADD (struct qeth_qdio_out_q*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_NOTIFY_GENERALERROR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buf_elements ; 
 int /*<<< orphan*/  bufs ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  qeth_notify_skbs (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*,int /*<<< orphan*/ ) ; 
 int skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skbs_csum ; 
 int /*<<< orphan*/  skbs_sg ; 
 int /*<<< orphan*/  skbs_tso ; 
 int /*<<< orphan*/  tso_bytes ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_errors ; 
 int /*<<< orphan*/  tx_packets ; 

__attribute__((used)) static void qeth_tx_complete_buf(struct qeth_qdio_out_buffer *buf, bool error,
				 int budget)
{
	struct qeth_qdio_out_q *queue = buf->q;
	struct sk_buff *skb;

	/* release may never happen from within CQ tasklet scope */
	WARN_ON_ONCE(atomic_read(&buf->state) == QETH_QDIO_BUF_IN_CQ);

	if (atomic_read(&buf->state) == QETH_QDIO_BUF_PENDING)
		qeth_notify_skbs(queue, buf, TX_NOTIFY_GENERALERROR);

	/* Empty buffer? */
	if (buf->next_element_to_fill == 0)
		return;

	QETH_TXQ_STAT_INC(queue, bufs);
	QETH_TXQ_STAT_ADD(queue, buf_elements, buf->next_element_to_fill);
	while ((skb = __skb_dequeue(&buf->skb_list)) != NULL) {
		unsigned int bytes = qdisc_pkt_len(skb);
		bool is_tso = skb_is_gso(skb);
		unsigned int packets;

		packets = is_tso ? skb_shinfo(skb)->gso_segs : 1;
		if (error) {
			QETH_TXQ_STAT_ADD(queue, tx_errors, packets);
		} else {
			QETH_TXQ_STAT_ADD(queue, tx_packets, packets);
			QETH_TXQ_STAT_ADD(queue, tx_bytes, bytes);
			if (skb->ip_summed == CHECKSUM_PARTIAL)
				QETH_TXQ_STAT_ADD(queue, skbs_csum, packets);
			if (skb_is_nonlinear(skb))
				QETH_TXQ_STAT_INC(queue, skbs_sg);
			if (is_tso) {
				QETH_TXQ_STAT_INC(queue, skbs_tso);
				QETH_TXQ_STAT_ADD(queue, tso_bytes, bytes);
			}
		}

		napi_consume_skb(skb, budget);
	}
}