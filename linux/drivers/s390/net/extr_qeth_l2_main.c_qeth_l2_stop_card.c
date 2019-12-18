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
struct TYPE_2__ {int /*<<< orphan*/  mac_bits; } ;
struct qeth_card {scalar_t__ state; TYPE_1__ info; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  rx_mode_work; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 scalar_t__ CARD_STATE_HARDSETUP ; 
 scalar_t__ CARD_STATE_SOFTSETUP ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_LAYER2_MAC_REGISTERED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_clear_ipacmd_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_clear_working_pool_list (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_drain_output_queues (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_l2_drain_rx_mode_cache (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_qdio_clear_card (struct qeth_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_set_allowed_threads (struct qeth_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qeth_l2_stop_card(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "stopcard");

	qeth_set_allowed_threads(card, 0, 1);

	cancel_work_sync(&card->rx_mode_work);
	qeth_l2_drain_rx_mode_cache(card);

	if (card->state == CARD_STATE_SOFTSETUP) {
		qeth_clear_ipacmd_list(card);
		card->state = CARD_STATE_HARDSETUP;
	}
	if (card->state == CARD_STATE_HARDSETUP) {
		qeth_qdio_clear_card(card, 0);
		qeth_drain_output_queues(card);
		qeth_clear_working_pool_list(card);
		card->state = CARD_STATE_DOWN;
	}

	flush_workqueue(card->event_wq);
	card->info.mac_bits &= ~QETH_LAYER2_MAC_REGISTERED;
}