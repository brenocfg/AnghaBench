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
struct qeth_qdio_out_q {int queue_no; int /*<<< orphan*/ ** bufs; int /*<<< orphan*/  timer; struct qeth_card* card; } ;
struct TYPE_2__ {int no_out_queues; int /*<<< orphan*/  state; int /*<<< orphan*/ * in_q; struct qeth_qdio_out_q** out_qs; } ;
struct qeth_card {TYPE_1__ qdio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,struct qeth_qdio_out_q**,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_QDIO_ALLOCATED ; 
 scalar_t__ QETH_QDIO_UNINITIALIZED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_alloc_buffer_pool (struct qeth_card*) ; 
 scalar_t__ qeth_alloc_cq (struct qeth_card*) ; 
 struct qeth_qdio_out_q* qeth_alloc_output_queue () ; 
 int /*<<< orphan*/ * qeth_alloc_qdio_queue () ; 
 int /*<<< orphan*/  qeth_free_buffer_pool (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_free_output_queue (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_free_qdio_queue (int /*<<< orphan*/ *) ; 
 scalar_t__ qeth_init_qdio_out_buf (struct qeth_qdio_out_q*,int) ; 
 int /*<<< orphan*/  qeth_qdio_outbuf_cache ; 
 int /*<<< orphan*/  qeth_tx_completion_timer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_alloc_qdio_queues(struct qeth_card *card)
{
	int i, j;

	QETH_CARD_TEXT(card, 2, "allcqdbf");

	if (atomic_cmpxchg(&card->qdio.state, QETH_QDIO_UNINITIALIZED,
		QETH_QDIO_ALLOCATED) != QETH_QDIO_UNINITIALIZED)
		return 0;

	QETH_CARD_TEXT(card, 2, "inq");
	card->qdio.in_q = qeth_alloc_qdio_queue();
	if (!card->qdio.in_q)
		goto out_nomem;

	/* inbound buffer pool */
	if (qeth_alloc_buffer_pool(card))
		goto out_freeinq;

	/* outbound */
	for (i = 0; i < card->qdio.no_out_queues; ++i) {
		struct qeth_qdio_out_q *queue;

		queue = qeth_alloc_output_queue();
		if (!queue)
			goto out_freeoutq;
		QETH_CARD_TEXT_(card, 2, "outq %i", i);
		QETH_CARD_HEX(card, 2, &queue, sizeof(void *));
		card->qdio.out_qs[i] = queue;
		queue->card = card;
		queue->queue_no = i;
		timer_setup(&queue->timer, qeth_tx_completion_timer, 0);

		/* give outbound qeth_qdio_buffers their qdio_buffers */
		for (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; ++j) {
			WARN_ON(queue->bufs[j]);
			if (qeth_init_qdio_out_buf(queue, j))
				goto out_freeoutqbufs;
		}
	}

	/* completion */
	if (qeth_alloc_cq(card))
		goto out_freeoutq;

	return 0;

out_freeoutqbufs:
	while (j > 0) {
		--j;
		kmem_cache_free(qeth_qdio_outbuf_cache,
				card->qdio.out_qs[i]->bufs[j]);
		card->qdio.out_qs[i]->bufs[j] = NULL;
	}
out_freeoutq:
	while (i > 0) {
		qeth_free_output_queue(card->qdio.out_qs[--i]);
		card->qdio.out_qs[i] = NULL;
	}
	qeth_free_buffer_pool(card);
out_freeinq:
	qeth_free_qdio_queue(card->qdio.in_q);
	card->qdio.in_q = NULL;
out_nomem:
	atomic_set(&card->qdio.state, QETH_QDIO_UNINITIALIZED);
	return -ENOMEM;
}