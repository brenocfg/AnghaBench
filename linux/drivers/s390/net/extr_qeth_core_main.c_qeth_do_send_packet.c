#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {int next_buf_to_fill; scalar_t__ max_elements; int /*<<< orphan*/  set_pci_flags_count; int /*<<< orphan*/  state; scalar_t__ do_pack; int /*<<< orphan*/  used_buffers; struct qeth_qdio_out_buffer** bufs; } ;
struct qeth_qdio_out_buffer {scalar_t__ next_element_to_fill; int /*<<< orphan*/  state; } ;
struct qeth_hdr {int dummy; } ;
struct qeth_card {int /*<<< orphan*/  dev; } ;
struct netdev_queue {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_OUT_Q_LOCKED ; 
 int /*<<< orphan*/  QETH_OUT_Q_LOCKED_FLUSH ; 
 scalar_t__ QETH_OUT_Q_UNLOCKED ; 
 scalar_t__ QETH_QDIO_BUF_EMPTY ; 
 scalar_t__ QETH_QDIO_BUF_PRIMED ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_ADD (struct qeth_qdio_out_q*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QETH_TXQ_STAT_INC (struct qeth_qdio_out_q*,int) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufs_pack ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 unsigned int qeth_fill_buffer (struct qeth_qdio_out_buffer*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qeth_flush_buffers (struct qeth_qdio_out_q*,int,int) ; 
 int /*<<< orphan*/  qeth_out_queue_is_full (struct qeth_qdio_out_q*) ; 
 int qeth_prep_flush_pack_buffer (struct qeth_qdio_out_q*) ; 
 int qeth_switch_to_nonpacking_if_needed (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_switch_to_packing_if_needed (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 
 int skbs_pack ; 

int qeth_do_send_packet(struct qeth_card *card, struct qeth_qdio_out_q *queue,
			struct sk_buff *skb, struct qeth_hdr *hdr,
			unsigned int offset, unsigned int hd_len,
			int elements_needed)
{
	struct qeth_qdio_out_buffer *buffer;
	unsigned int next_element;
	struct netdev_queue *txq;
	bool stopped = false;
	int start_index;
	int flush_count = 0;
	int do_pack = 0;
	int tmp;
	int rc = 0;

	/* spin until we get the queue ... */
	while (atomic_cmpxchg(&queue->state, QETH_OUT_Q_UNLOCKED,
			      QETH_OUT_Q_LOCKED) != QETH_OUT_Q_UNLOCKED);
	start_index = queue->next_buf_to_fill;
	buffer = queue->bufs[queue->next_buf_to_fill];

	/* Just a sanity check, the wake/stop logic should ensure that we always
	 * get a free buffer.
	 */
	if (atomic_read(&buffer->state) != QETH_QDIO_BUF_EMPTY) {
		atomic_set(&queue->state, QETH_OUT_Q_UNLOCKED);
		return -EBUSY;
	}

	txq = netdev_get_tx_queue(card->dev, skb_get_queue_mapping(skb));

	/* check if we need to switch packing state of this queue */
	qeth_switch_to_packing_if_needed(queue);
	if (queue->do_pack) {
		do_pack = 1;
		/* does packet fit in current buffer? */
		if (buffer->next_element_to_fill + elements_needed >
		    queue->max_elements) {
			/* ... no -> set state PRIMED */
			atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
			flush_count++;
			queue->next_buf_to_fill =
				(queue->next_buf_to_fill + 1) %
				QDIO_MAX_BUFFERS_PER_Q;
			buffer = queue->bufs[queue->next_buf_to_fill];

			/* We stepped forward, so sanity-check again: */
			if (atomic_read(&buffer->state) !=
			    QETH_QDIO_BUF_EMPTY) {
				qeth_flush_buffers(queue, start_index,
							   flush_count);
				atomic_set(&queue->state,
						QETH_OUT_Q_UNLOCKED);
				rc = -EBUSY;
				goto out;
			}
		}
	}

	if (buffer->next_element_to_fill == 0 &&
	    atomic_inc_return(&queue->used_buffers) >= QDIO_MAX_BUFFERS_PER_Q) {
		/* If a TX completion happens right _here_ and misses to wake
		 * the txq, then our re-check below will catch the race.
		 */
		QETH_TXQ_STAT_INC(queue, stopped);
		netif_tx_stop_queue(txq);
		stopped = true;
	}

	next_element = qeth_fill_buffer(buffer, skb, hdr, offset, hd_len);

	if (queue->do_pack)
		QETH_TXQ_STAT_INC(queue, skbs_pack);
	if (!queue->do_pack || stopped || next_element >= queue->max_elements) {
		flush_count++;
		atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
		queue->next_buf_to_fill = (queue->next_buf_to_fill + 1) %
					  QDIO_MAX_BUFFERS_PER_Q;
	}

	if (flush_count)
		qeth_flush_buffers(queue, start_index, flush_count);
	else if (!atomic_read(&queue->set_pci_flags_count))
		atomic_xchg(&queue->state, QETH_OUT_Q_LOCKED_FLUSH);
	/*
	 * queue->state will go from LOCKED -> UNLOCKED or from
	 * LOCKED_FLUSH -> LOCKED if output_handler wanted to 'notify' us
	 * (switch packing state or flush buffer to get another pci flag out).
	 * In that case we will enter this loop
	 */
	while (atomic_dec_return(&queue->state)) {
		start_index = queue->next_buf_to_fill;
		/* check if we can go back to non-packing state */
		tmp = qeth_switch_to_nonpacking_if_needed(queue);
		/*
		 * check if we need to flush a packing buffer to get a pci
		 * flag out on the queue
		 */
		if (!tmp && !atomic_read(&queue->set_pci_flags_count))
			tmp = qeth_prep_flush_pack_buffer(queue);
		if (tmp) {
			qeth_flush_buffers(queue, start_index, tmp);
			flush_count += tmp;
		}
	}
out:
	/* at this point the queue is UNLOCKED again */
	if (do_pack)
		QETH_TXQ_STAT_ADD(queue, bufs_pack, flush_count);

	if (stopped && !qeth_out_queue_is_full(queue))
		netif_tx_start_queue(txq);
	return rc;
}