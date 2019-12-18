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
struct gelic_descr {struct gelic_descr* next; int /*<<< orphan*/  skb; } ;
struct TYPE_2__ {struct gelic_descr* head; } ;
struct gelic_card {TYPE_1__ rx_chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  gelic_card_release_rx_chain (struct gelic_card*) ; 
 int gelic_descr_prepare_rx (struct gelic_card*,struct gelic_descr*) ; 

__attribute__((used)) static int gelic_card_fill_rx_chain(struct gelic_card *card)
{
	struct gelic_descr *descr = card->rx_chain.head;
	int ret;

	do {
		if (!descr->skb) {
			ret = gelic_descr_prepare_rx(card, descr);
			if (ret)
				goto rewind;
		}
		descr = descr->next;
	} while (descr != card->rx_chain.head);

	return 0;
rewind:
	gelic_card_release_rx_chain(card);
	return ret;
}