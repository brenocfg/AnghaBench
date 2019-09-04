#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int dmaaddr; scalar_t__ dmabuf; } ;
struct avmcard_dmainfo {scalar_t__ recvlen; int /*<<< orphan*/  send_queue; TYPE_1__ recvbuf; } ;
struct TYPE_9__ {int csr; int /*<<< orphan*/  lock; struct avmcard_dmainfo* dma; } ;
typedef  TYPE_2__ avmcard ;

/* Variables and functions */
 int ALL_INT ; 
 int /*<<< orphan*/  AMCC_INTCSR ; 
 int /*<<< orphan*/  AMCC_RXLEN ; 
 int /*<<< orphan*/  AMCC_RXPTR ; 
 int ANY_S5933_INT ; 
 int EN_RX_TC_INT ; 
 int EN_TX_TC_INT ; 
 int RX_TC_INT ; 
 int TX_TC_INT ; 
 int /*<<< orphan*/  b1dma_dispatch_tx (TYPE_2__*) ; 
 int /*<<< orphan*/  b1dma_handle_rx (TYPE_2__*) ; 
 int b1dma_readl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1dma_writel (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b1dma_handle_interrupt(avmcard *card)
{
	u32 status;
	u32 newcsr;

	spin_lock(&card->lock);

	status = b1dma_readl(card, AMCC_INTCSR);
	if ((status & ANY_S5933_INT) == 0) {
		spin_unlock(&card->lock);
		return;
	}

	newcsr = card->csr | (status & ALL_INT);
	if (status & TX_TC_INT) newcsr &= ~EN_TX_TC_INT;
	if (status & RX_TC_INT) newcsr &= ~EN_RX_TC_INT;
	b1dma_writel(card, newcsr, AMCC_INTCSR);

	if ((status & RX_TC_INT) != 0) {
		struct avmcard_dmainfo *dma = card->dma;
		u32 rxlen;
		if (card->dma->recvlen == 0) {
			rxlen = b1dma_readl(card, AMCC_RXLEN);
			if (rxlen == 0) {
				dma->recvlen = *((u32 *)dma->recvbuf.dmabuf);
				rxlen = (dma->recvlen + 3) & ~3;
				b1dma_writel(card, dma->recvbuf.dmaaddr + 4, AMCC_RXPTR);
				b1dma_writel(card, rxlen, AMCC_RXLEN);
#ifdef AVM_B1DMA_DEBUG
			} else {
				printk(KERN_ERR "%s: rx not complete (%d).\n",
				       card->name, rxlen);
#endif
			}
		} else {
			spin_unlock(&card->lock);
			b1dma_handle_rx(card);
			dma->recvlen = 0;
			spin_lock(&card->lock);
			b1dma_writel(card, dma->recvbuf.dmaaddr, AMCC_RXPTR);
			b1dma_writel(card, 4, AMCC_RXLEN);
		}
	}

	if ((status & TX_TC_INT) != 0) {
		if (skb_queue_empty(&card->dma->send_queue))
			card->csr &= ~EN_TX_TC_INT;
		else
			b1dma_dispatch_tx(card);
	}
	b1dma_writel(card, card->csr, AMCC_INTCSR);

	spin_unlock(&card->lock);
}