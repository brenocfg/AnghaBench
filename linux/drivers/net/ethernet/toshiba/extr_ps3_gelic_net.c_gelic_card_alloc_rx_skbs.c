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
struct gelic_descr_chain {int /*<<< orphan*/  tail; } ;
struct gelic_card {TYPE_1__* rx_top; struct gelic_descr_chain rx_chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;

/* Variables and functions */
 int gelic_card_fill_rx_chain (struct gelic_card*) ; 

__attribute__((used)) static int gelic_card_alloc_rx_skbs(struct gelic_card *card)
{
	struct gelic_descr_chain *chain;
	int ret;
	chain = &card->rx_chain;
	ret = gelic_card_fill_rx_chain(card);
	chain->tail = card->rx_top->prev; /* point to the last */
	return ret;
}