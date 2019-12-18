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
struct TYPE_5__ {int /*<<< orphan*/  entry_list; int /*<<< orphan*/  buf_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry_list; int /*<<< orphan*/  buf_count; } ;
struct TYPE_6__ {int no_in_queues; TYPE_2__ init_pool; TYPE_1__ in_buf_pool; int /*<<< orphan*/  in_buf_size; int /*<<< orphan*/  default_out_queue; int /*<<< orphan*/  do_prio_queueing; int /*<<< orphan*/  state; } ;
struct qeth_card {TYPE_3__ qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_DEFAULT_QUEUE ; 
 int /*<<< orphan*/  QETH_IN_BUF_COUNT_DEFAULT ; 
 int /*<<< orphan*/  QETH_IN_BUF_COUNT_HSDEFAULT ; 
 int /*<<< orphan*/  QETH_IN_BUF_SIZE_DEFAULT ; 
 int /*<<< orphan*/  QETH_PRIOQ_DEFAULT ; 
 int /*<<< orphan*/  QETH_QDIO_UNINITIALIZED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qeth_init_qdio_info(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 4, "intqdinf");
	atomic_set(&card->qdio.state, QETH_QDIO_UNINITIALIZED);
	card->qdio.do_prio_queueing = QETH_PRIOQ_DEFAULT;
	card->qdio.default_out_queue = QETH_DEFAULT_QUEUE;

	/* inbound */
	card->qdio.no_in_queues = 1;
	card->qdio.in_buf_size = QETH_IN_BUF_SIZE_DEFAULT;
	if (IS_IQD(card))
		card->qdio.init_pool.buf_count = QETH_IN_BUF_COUNT_HSDEFAULT;
	else
		card->qdio.init_pool.buf_count = QETH_IN_BUF_COUNT_DEFAULT;
	card->qdio.in_buf_pool.buf_count = card->qdio.init_pool.buf_count;
	INIT_LIST_HEAD(&card->qdio.in_buf_pool.entry_list);
	INIT_LIST_HEAD(&card->qdio.init_pool.entry_list);
}