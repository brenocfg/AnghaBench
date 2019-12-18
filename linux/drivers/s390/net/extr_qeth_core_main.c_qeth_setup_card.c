#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  entries; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct qeth_card {int /*<<< orphan*/  close_dev_work; int /*<<< orphan*/  buffer_reclaim_work; TYPE_3__ ipato; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  cmd_waiter_list; int /*<<< orphan*/  kernel_thread_starter; int /*<<< orphan*/  discipline_mutex; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  thread_mask_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver_info; } ;
struct TYPE_8__ {TYPE_2__ id; } ;

/* Variables and functions */
 TYPE_4__* CARD_RDEV (struct qeth_card*) ; 
 int /*<<< orphan*/  CARD_STATE_DOWN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qeth_buffer_reclaim_work ; 
 int /*<<< orphan*/  qeth_close_dev_handler ; 
 int /*<<< orphan*/  qeth_init_qdio_info (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_set_initial_options (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_start_kernel_thread ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_setup_card(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "setupcrd");

	card->info.type = CARD_RDEV(card)->id.driver_info;
	card->state = CARD_STATE_DOWN;
	spin_lock_init(&card->lock);
	spin_lock_init(&card->thread_mask_lock);
	mutex_init(&card->conf_mutex);
	mutex_init(&card->discipline_mutex);
	INIT_WORK(&card->kernel_thread_starter, qeth_start_kernel_thread);
	INIT_LIST_HEAD(&card->cmd_waiter_list);
	init_waitqueue_head(&card->wait_q);
	qeth_set_initial_options(card);
	/* IP address takeover */
	INIT_LIST_HEAD(&card->ipato.entries);
	qeth_init_qdio_info(card);
	INIT_DELAYED_WORK(&card->buffer_reclaim_work, qeth_buffer_reclaim_work);
	INIT_WORK(&card->close_dev_work, qeth_close_dev_handler);
}