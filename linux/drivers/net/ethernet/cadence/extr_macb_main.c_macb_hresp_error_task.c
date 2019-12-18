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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct macb_queue {int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  rx_ring_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mog_init_rings ) (struct macb*) ;} ;
struct macb {unsigned int num_queues; int rx_intr_mask; int hw_dma_cap; struct macb_queue* queues; TYPE_1__ macbgem_ops; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRESP ; 
 int HW_DMA_CAP_64B ; 
 int /*<<< orphan*/  IDR ; 
 int /*<<< orphan*/  IER ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int MACB_TX_INT_FLAGS ; 
 int /*<<< orphan*/  NCR ; 
 int /*<<< orphan*/  RBQP ; 
 int /*<<< orphan*/  RBQPH ; 
 int /*<<< orphan*/  RE ; 
 int /*<<< orphan*/  TBQP ; 
 int /*<<< orphan*/  TBQPH ; 
 int /*<<< orphan*/  TE ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  queue_writel (struct macb_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct macb*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macb_hresp_error_task(unsigned long data)
{
	struct macb *bp = (struct macb *)data;
	struct net_device *dev = bp->dev;
	struct macb_queue *queue = bp->queues;
	unsigned int q;
	u32 ctrl;

	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		queue_writel(queue, IDR, bp->rx_intr_mask |
					 MACB_TX_INT_FLAGS |
					 MACB_BIT(HRESP));
	}
	ctrl = macb_readl(bp, NCR);
	ctrl &= ~(MACB_BIT(RE) | MACB_BIT(TE));
	macb_writel(bp, NCR, ctrl);

	netif_tx_stop_all_queues(dev);
	netif_carrier_off(dev);

	bp->macbgem_ops.mog_init_rings(bp);

	/* Initialize TX and RX buffers */
	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		queue_writel(queue, RBQP, lower_32_bits(queue->rx_ring_dma));
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (bp->hw_dma_cap & HW_DMA_CAP_64B)
			queue_writel(queue, RBQPH,
				     upper_32_bits(queue->rx_ring_dma));
#endif
		queue_writel(queue, TBQP, lower_32_bits(queue->tx_ring_dma));
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (bp->hw_dma_cap & HW_DMA_CAP_64B)
			queue_writel(queue, TBQPH,
				     upper_32_bits(queue->tx_ring_dma));
#endif

		/* Enable interrupts */
		queue_writel(queue, IER,
			     bp->rx_intr_mask |
			     MACB_TX_INT_FLAGS |
			     MACB_BIT(HRESP));
	}

	ctrl |= MACB_BIT(RE) | MACB_BIT(TE);
	macb_writel(bp, NCR, ctrl);

	netif_carrier_on(dev);
	netif_tx_start_all_queues(dev);
}