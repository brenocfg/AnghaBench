#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ tx_idx; TYPE_2__* tx_skb; int /*<<< orphan*/  timer; int /*<<< orphan*/  Flags; } ;
struct w6692_hw {TYPE_1__ dch; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int /*<<< orphan*/  W6692_fill_Dfifo (struct w6692_hw*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 scalar_t__ get_next_dframe (TYPE_1__*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_txD(struct w6692_hw *card) {
	if (test_and_clear_bit(FLG_BUSY_TIMER, &card->dch.Flags))
		del_timer(&card->dch.timer);
	if (card->dch.tx_skb && card->dch.tx_idx < card->dch.tx_skb->len) {
		W6692_fill_Dfifo(card);
	} else {
		dev_kfree_skb(card->dch.tx_skb);
		if (get_next_dframe(&card->dch))
			W6692_fill_Dfifo(card);
	}
}