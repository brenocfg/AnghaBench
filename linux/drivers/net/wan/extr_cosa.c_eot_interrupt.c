#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cosa_data {int txchan; int rxsize; int* rxbuf; int* bouncebuf; int /*<<< orphan*/  lock; scalar_t__ rxtx; int /*<<< orphan*/  num; int /*<<< orphan*/  rxbitmap; TYPE_1__* rxchan; int /*<<< orphan*/  txbitmap; int /*<<< orphan*/  txsize; struct channel_data* chan; int /*<<< orphan*/  dma; } ;
struct channel_data {int /*<<< orphan*/  num; scalar_t__ (* tx_done ) (struct channel_data*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  num; scalar_t__ (* rx_done ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RXBIT ; 
 int /*<<< orphan*/  TXBIT ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosa_dma_able (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_driver_status_nolock (struct cosa_data*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct channel_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static inline void eot_interrupt(struct cosa_data *cosa, int status)
{
	unsigned long flags, flags1;
	spin_lock_irqsave(&cosa->lock, flags);
	flags1 = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	release_dma_lock(flags1);
	if (test_bit(TXBIT, &cosa->rxtx)) {
		struct channel_data *chan = cosa->chan+cosa->txchan;
		if (chan->tx_done)
			if (chan->tx_done(chan, cosa->txsize))
				clear_bit(chan->num, &cosa->txbitmap);
	} else if (test_bit(RXBIT, &cosa->rxtx)) {
#ifdef DEBUG_DATA
	{
		int i;
		pr_info("cosa%dc%d: done rx(0x%x)",
			cosa->num, cosa->rxchan->num, cosa->rxsize);
		for (i=0; i<cosa->rxsize; i++)
			pr_cont(" %02x", cosa->rxbuf[i]&0xff);
		pr_cont("\n");
	}
#endif
		/* Packet for unknown channel? */
		if (cosa->rxbuf == cosa->bouncebuf)
			goto out;
		if (!cosa_dma_able(cosa->rxchan, cosa->rxbuf, cosa->rxsize))
			memcpy(cosa->rxbuf, cosa->bouncebuf, cosa->rxsize);
		if (cosa->rxchan->rx_done)
			if (cosa->rxchan->rx_done(cosa->rxchan))
				clear_bit(cosa->rxchan->num, &cosa->rxbitmap);
	} else {
		pr_notice("cosa%d: unexpected EOT interrupt\n", cosa->num);
	}
	/*
	 * Clear the RXBIT, TXBIT and IRQBIT (the latest should be
	 * cleared anyway). We should do it as soon as possible
	 * so that we can tell the COSA we are done and to give it a time
	 * for recovery.
	 */
out:
	cosa->rxtx = 0;
	put_driver_status_nolock(cosa);
	spin_unlock_irqrestore(&cosa->lock, flags);
}