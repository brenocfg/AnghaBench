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
struct timer_list {int dummy; } ;
struct fw_transaction {unsigned long long tlabel; int /*<<< orphan*/  callback_data; int /*<<< orphan*/  (* callback ) (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  link; struct fw_card* card; } ;
struct fw_card {unsigned long long tlabel_mask; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_CANCELLED ; 
 struct fw_transaction* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  split_timeout_timer ; 
 int /*<<< orphan*/  stub1 (struct fw_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fw_transaction* t ; 

__attribute__((used)) static void split_transaction_timeout_callback(struct timer_list *timer)
{
	struct fw_transaction *t = from_timer(t, timer, split_timeout_timer);
	struct fw_card *card = t->card;
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);
	if (list_empty(&t->link)) {
		spin_unlock_irqrestore(&card->lock, flags);
		return;
	}
	list_del(&t->link);
	card->tlabel_mask &= ~(1ULL << t->tlabel);
	spin_unlock_irqrestore(&card->lock, flags);

	t->callback(card, RCODE_CANCELLED, NULL, 0, t->callback_data);
}