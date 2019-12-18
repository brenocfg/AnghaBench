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
struct net_device {scalar_t__ irq; } ;
struct lance_regs {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {scalar_t__ dma_irq; int /*<<< orphan*/  multicast_timer; struct lance_regs* ll; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_REG_SSR ; 
 int IO_SSR_LANCE_DMA_EN ; 
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fast_iob () ; 
 int /*<<< orphan*/  fast_mb () ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int ioasic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioasic_ssr_lock ; 
 int /*<<< orphan*/  ioasic_write (int /*<<< orphan*/ ,int) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lance_close(struct net_device *dev)
{
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_regs *ll = lp->ll;

	netif_stop_queue(dev);
	del_timer_sync(&lp->multicast_timer);

	/* Stop the card */
	writereg(&ll->rap, LE_CSR0);
	writereg(&ll->rdp, LE_C0_STOP);

	if (lp->dma_irq >= 0) {
		unsigned long flags;

		spin_lock_irqsave(&ioasic_ssr_lock, flags);

		fast_mb();
		/* Disable I/O ASIC LANCE DMA.  */
		ioasic_write(IO_REG_SSR,
			     ioasic_read(IO_REG_SSR) & ~IO_SSR_LANCE_DMA_EN);

		fast_iob();
		spin_unlock_irqrestore(&ioasic_ssr_lock, flags);

		free_irq(lp->dma_irq, dev);
	}
	free_irq(dev->irq, dev);
	return 0;
}