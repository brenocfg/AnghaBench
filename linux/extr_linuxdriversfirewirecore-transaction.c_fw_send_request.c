#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  callback; } ;
struct fw_transaction {int node_id; int tlabel; int is_split_transaction; TYPE_2__ packet; int /*<<< orphan*/  link; void* callback_data; int /*<<< orphan*/  (* callback ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  split_timeout_timer; struct fw_card* card; } ;
struct fw_card {TYPE_1__* driver; int /*<<< orphan*/  lock; int /*<<< orphan*/  transaction_list; int /*<<< orphan*/  node_id; } ;
typedef  int /*<<< orphan*/  (* fw_transaction_callback_t ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;
struct TYPE_4__ {int /*<<< orphan*/  (* send_request ) (struct fw_card*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_SEND_ERROR ; 
 int allocate_tlabel (struct fw_card*) ; 
 int /*<<< orphan*/  fw_fill_request (TYPE_2__*,int,int,int,int /*<<< orphan*/ ,int,int,unsigned long long,void*,size_t) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  split_transaction_timeout_callback ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transmit_complete_callback ; 

void fw_send_request(struct fw_card *card, struct fw_transaction *t, int tcode,
		     int destination_id, int generation, int speed,
		     unsigned long long offset, void *payload, size_t length,
		     fw_transaction_callback_t callback, void *callback_data)
{
	unsigned long flags;
	int tlabel;

	/*
	 * Allocate tlabel from the bitmap and put the transaction on
	 * the list while holding the card spinlock.
	 */

	spin_lock_irqsave(&card->lock, flags);

	tlabel = allocate_tlabel(card);
	if (tlabel < 0) {
		spin_unlock_irqrestore(&card->lock, flags);
		callback(card, RCODE_SEND_ERROR, NULL, 0, callback_data);
		return;
	}

	t->node_id = destination_id;
	t->tlabel = tlabel;
	t->card = card;
	t->is_split_transaction = false;
	timer_setup(&t->split_timeout_timer,
		    split_transaction_timeout_callback, 0);
	t->callback = callback;
	t->callback_data = callback_data;

	fw_fill_request(&t->packet, tcode, t->tlabel,
			destination_id, card->node_id, generation,
			speed, offset, payload, length);
	t->packet.callback = transmit_complete_callback;

	list_add_tail(&t->link, &card->transaction_list);

	spin_unlock_irqrestore(&card->lock, flags);

	card->driver->send_request(card, &t->packet);
}