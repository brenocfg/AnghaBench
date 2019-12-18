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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct gelic_card {int irq_status; int irq_mask; int /*<<< orphan*/ * netdev; int /*<<< orphan*/  tx_lock; TYPE_1__ tx_chain; scalar_t__ tx_dma_progress; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GELIC_CARD_PORT_STATUS_CHANGED ; 
 int GELIC_CARD_RXINT ; 
 int GELIC_CARD_TXINT ; 
 int GELIC_CARD_WLAN_COMMAND_COMPLETED ; 
 int GELIC_CARD_WLAN_EVENT_RECEIVED ; 
 size_t GELIC_PORT_WIRELESS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  gelic_card_get_ether_port_status (struct gelic_card*,int) ; 
 int /*<<< orphan*/  gelic_card_kick_txdma (struct gelic_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_card_release_tx_chain (struct gelic_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_card_rx_irq_off (struct gelic_card*) ; 
 int /*<<< orphan*/  gelic_wl_interrupt (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t gelic_card_interrupt(int irq, void *ptr)
{
	unsigned long flags;
	struct gelic_card *card = ptr;
	u64 status;

	status = card->irq_status;

	if (!status)
		return IRQ_NONE;

	status &= card->irq_mask;

	if (status & GELIC_CARD_RXINT) {
		gelic_card_rx_irq_off(card);
		napi_schedule(&card->napi);
	}

	if (status & GELIC_CARD_TXINT) {
		spin_lock_irqsave(&card->tx_lock, flags);
		card->tx_dma_progress = 0;
		gelic_card_release_tx_chain(card, 0);
		/* kick outstanding tx descriptor if any */
		gelic_card_kick_txdma(card, card->tx_chain.tail);
		spin_unlock_irqrestore(&card->tx_lock, flags);
	}

	/* ether port status changed */
	if (status & GELIC_CARD_PORT_STATUS_CHANGED)
		gelic_card_get_ether_port_status(card, 1);

#ifdef CONFIG_GELIC_WIRELESS
	if (status & (GELIC_CARD_WLAN_EVENT_RECEIVED |
		      GELIC_CARD_WLAN_COMMAND_COMPLETED))
		gelic_wl_interrupt(card->netdev[GELIC_PORT_WIRELESS], status);
#endif

	return IRQ_HANDLED;
}