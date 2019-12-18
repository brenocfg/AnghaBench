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
struct qeth_rx {int dummy; } ;
struct qeth_qdio_out_q {int /*<<< orphan*/  state; int /*<<< orphan*/  set_pci_flags_count; int /*<<< orphan*/  used_buffers; scalar_t__ bulk_start; int /*<<< orphan*/ * prev_hdr; scalar_t__ do_pack; scalar_t__ next_buf_to_fill; int /*<<< orphan*/  max_elements; int /*<<< orphan*/  qdio_bufs; } ;
struct TYPE_5__ {int buf_count; } ;
struct TYPE_6__ {unsigned int no_out_queues; struct qeth_qdio_out_q** out_qs; TYPE_2__ in_buf_pool; TYPE_1__* in_q; } ;
struct qeth_card {int /*<<< orphan*/  dev; TYPE_3__ qdio; int /*<<< orphan*/  rx; } ;
struct TYPE_4__ {int next_buf_to_init; int /*<<< orphan*/ * bufs; int /*<<< orphan*/  qdio_bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  QDIO_FLAG_SYNC_INPUT ; 
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT_ (struct qeth_card*,int,char*,int) ; 
 int /*<<< orphan*/  QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_OUT_Q_UNLOCKED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int do_QDIO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_reset_buffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qeth_cq_init (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_init_input_buffer (struct qeth_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_initialize_working_pool_list (struct qeth_card*) ; 

int qeth_init_qdio_queues(struct qeth_card *card)
{
	unsigned int i;
	int rc;

	QETH_CARD_TEXT(card, 2, "initqdqs");

	/* inbound queue */
	qdio_reset_buffers(card->qdio.in_q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
	memset(&card->rx, 0, sizeof(struct qeth_rx));
	qeth_initialize_working_pool_list(card);
	/*give only as many buffers to hardware as we have buffer pool entries*/
	for (i = 0; i < card->qdio.in_buf_pool.buf_count - 1; ++i)
		qeth_init_input_buffer(card, &card->qdio.in_q->bufs[i]);
	card->qdio.in_q->next_buf_to_init =
		card->qdio.in_buf_pool.buf_count - 1;
	rc = do_QDIO(CARD_DDEV(card), QDIO_FLAG_SYNC_INPUT, 0, 0,
		     card->qdio.in_buf_pool.buf_count - 1);
	if (rc) {
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
		return rc;
	}

	/* completion */
	rc = qeth_cq_init(card);
	if (rc) {
		return rc;
	}

	/* outbound queue */
	for (i = 0; i < card->qdio.no_out_queues; ++i) {
		struct qeth_qdio_out_q *queue = card->qdio.out_qs[i];

		qdio_reset_buffers(queue->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
		queue->max_elements = QETH_MAX_BUFFER_ELEMENTS(card);
		queue->next_buf_to_fill = 0;
		queue->do_pack = 0;
		queue->prev_hdr = NULL;
		queue->bulk_start = 0;
		atomic_set(&queue->used_buffers, 0);
		atomic_set(&queue->set_pci_flags_count, 0);
		atomic_set(&queue->state, QETH_OUT_Q_UNLOCKED);
		netdev_tx_reset_queue(netdev_get_tx_queue(card->dev, i));
	}
	return 0;
}