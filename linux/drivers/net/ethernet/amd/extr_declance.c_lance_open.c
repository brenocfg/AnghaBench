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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {scalar_t__ irq; int /*<<< orphan*/  name; scalar_t__ mem_start; } ;
struct lance_regs {int /*<<< orphan*/  rdp; int /*<<< orphan*/  rap; } ;
struct lance_private {scalar_t__ dma_irq; int /*<<< orphan*/  type; struct lance_regs* ll; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  IO_REG_SSR ; 
 int IO_SSR_LANCE_DMA_EN ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  LE_C0_STOP ; 
 int /*<<< orphan*/  LE_CSR0 ; 
 int /*<<< orphan*/  fast_mb () ; 
 int /*<<< orphan*/ * filter ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct net_device*) ; 
 int init_restart_lance (struct lance_private*) ; 
 int ioasic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioasic_ssr_lock ; 
 int /*<<< orphan*/  ioasic_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lance_dma_merr_int ; 
 int /*<<< orphan*/  lance_init_ring (struct net_device*) ; 
 int /*<<< orphan*/  lance_interrupt ; 
 scalar_t__* lib_ptr (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_csrs (struct lance_private*) ; 
 int /*<<< orphan*/  mode ; 
 struct lance_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lance_open(struct net_device *dev)
{
	volatile u16 *ib = (volatile u16 *)dev->mem_start;
	struct lance_private *lp = netdev_priv(dev);
	volatile struct lance_regs *ll = lp->ll;
	int status = 0;

	/* Stop the Lance */
	writereg(&ll->rap, LE_CSR0);
	writereg(&ll->rdp, LE_C0_STOP);

	/* Set mode and clear multicast filter only at device open,
	 * so that lance_init_ring() called at any error will not
	 * forget multicast filters.
	 *
	 * BTW it is common bug in all lance drivers! --ANK
	 */
	*lib_ptr(ib, mode, lp->type) = 0;
	*lib_ptr(ib, filter[0], lp->type) = 0;
	*lib_ptr(ib, filter[1], lp->type) = 0;
	*lib_ptr(ib, filter[2], lp->type) = 0;
	*lib_ptr(ib, filter[3], lp->type) = 0;

	lance_init_ring(dev);
	load_csrs(lp);

	netif_start_queue(dev);

	/* Associate IRQ with lance_interrupt */
	if (request_irq(dev->irq, lance_interrupt, 0, "lance", dev)) {
		printk("%s: Can't get IRQ %d\n", dev->name, dev->irq);
		return -EAGAIN;
	}
	if (lp->dma_irq >= 0) {
		unsigned long flags;

		if (request_irq(lp->dma_irq, lance_dma_merr_int, IRQF_ONESHOT,
				"lance error", dev)) {
			free_irq(dev->irq, dev);
			printk("%s: Can't get DMA IRQ %d\n", dev->name,
				lp->dma_irq);
			return -EAGAIN;
		}

		spin_lock_irqsave(&ioasic_ssr_lock, flags);

		fast_mb();
		/* Enable I/O ASIC LANCE DMA.  */
		ioasic_write(IO_REG_SSR,
			     ioasic_read(IO_REG_SSR) | IO_SSR_LANCE_DMA_EN);

		fast_mb();
		spin_unlock_irqrestore(&ioasic_ssr_lock, flags);
	}

	status = init_restart_lance(lp);
	return status;
}