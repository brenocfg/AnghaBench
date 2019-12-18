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
struct cosa_data {int rxsize; int nchannels; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma; int /*<<< orphan*/ * bouncebuf; int /*<<< orphan*/ * rxbuf; TYPE_1__* rxchan; int /*<<< orphan*/  num; TYPE_1__* chan; int /*<<< orphan*/  name; int /*<<< orphan*/  rxtx; } ;
struct TYPE_3__ {int num; int /*<<< orphan*/ * (* setup_rx ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DRIVER_RX_READY ; 
 int /*<<< orphan*/  IRQBIT ; 
 int /*<<< orphan*/  RXBIT ; 
 int SR_RX_DMA_ENA ; 
 int SR_TX_RDY ; 
 int SR_USR_INT_ENA ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 scalar_t__ cosa_dma_able (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int cosa_getdata16 (struct cosa_data*) ; 
 int cosa_getdata8 (struct cosa_data*) ; 
 int /*<<< orphan*/  cosa_putdata8 (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cosa_putstatus (struct cosa_data*,int) ; 
 int /*<<< orphan*/  debug_data_cmd (struct cosa_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_data_in (struct cosa_data*,int) ; 
 int /*<<< orphan*/  debug_status_out (struct cosa_data*,int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ is_8bit (struct cosa_data*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_driver_status_nolock (struct cosa_data*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_bus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rx_interrupt(struct cosa_data *cosa, int status)
{
	unsigned long flags;
#ifdef DEBUG_IRQS
	pr_info("cosa%d: SR_UP_REQUEST\n", cosa->num);
#endif

	spin_lock_irqsave(&cosa->lock, flags);
	set_bit(RXBIT, &cosa->rxtx);

	if (is_8bit(cosa)) {
		if (!test_bit(IRQBIT, &cosa->rxtx)) {
			set_bit(IRQBIT, &cosa->rxtx);
			put_driver_status_nolock(cosa);
			cosa->rxsize = cosa_getdata8(cosa) <<8;
#ifdef DEBUG_IO
			debug_data_in(cosa, cosa->rxsize >> 8);
#endif
			spin_unlock_irqrestore(&cosa->lock, flags);
			return;
		} else {
			clear_bit(IRQBIT, &cosa->rxtx);
			cosa->rxsize |= cosa_getdata8(cosa) & 0xff;
#ifdef DEBUG_IO
			debug_data_in(cosa, cosa->rxsize & 0xff);
#endif
#if 0
			pr_info("cosa%d: receive rxsize = (0x%04x)\n",
				cosa->num, cosa->rxsize);
#endif
		}
	} else {
		cosa->rxsize = cosa_getdata16(cosa);
#ifdef DEBUG_IO
		debug_data_in(cosa, cosa->rxsize);
#endif
#if 0
		pr_info("cosa%d: receive rxsize = (0x%04x)\n",
			cosa->num, cosa->rxsize);
#endif
	}
	if (((cosa->rxsize & 0xe000) >> 13) >= cosa->nchannels) {
		pr_warn("%s: rx for unknown channel (0x%04x)\n",
			cosa->name, cosa->rxsize);
		spin_unlock_irqrestore(&cosa->lock, flags);
		goto reject;
	}
	cosa->rxchan = cosa->chan + ((cosa->rxsize & 0xe000) >> 13);
	cosa->rxsize &= 0x1fff;
	spin_unlock_irqrestore(&cosa->lock, flags);

	cosa->rxbuf = NULL;
	if (cosa->rxchan->setup_rx)
		cosa->rxbuf = cosa->rxchan->setup_rx(cosa->rxchan, cosa->rxsize);

	if (!cosa->rxbuf) {
reject:		/* Reject the packet */
		pr_info("cosa%d: rejecting packet on channel %d\n",
			cosa->num, cosa->rxchan->num);
		cosa->rxbuf = cosa->bouncebuf;
	}

	/* start the DMA */
	flags = claim_dma_lock();
	disable_dma(cosa->dma);
	clear_dma_ff(cosa->dma);
	set_dma_mode(cosa->dma, DMA_MODE_READ);
	if (cosa_dma_able(cosa->rxchan, cosa->rxbuf, cosa->rxsize & 0x1fff)) {
		set_dma_addr(cosa->dma, virt_to_bus(cosa->rxbuf));
	} else {
		set_dma_addr(cosa->dma, virt_to_bus(cosa->bouncebuf));
	}
	set_dma_count(cosa->dma, (cosa->rxsize&0x1fff));
	enable_dma(cosa->dma);
	release_dma_lock(flags);
	spin_lock_irqsave(&cosa->lock, flags);
	cosa_putstatus(cosa, SR_RX_DMA_ENA|SR_USR_INT_ENA);
	if (!is_8bit(cosa) && (status & SR_TX_RDY))
		cosa_putdata8(cosa, DRIVER_RX_READY);
#ifdef DEBUG_IO
	debug_status_out(cosa, SR_RX_DMA_ENA|SR_USR_INT_ENA);
	if (!is_8bit(cosa) && (status & SR_TX_RDY))
		debug_data_cmd(cosa, DRIVER_RX_READY);
#endif
	spin_unlock_irqrestore(&cosa->lock, flags);
}