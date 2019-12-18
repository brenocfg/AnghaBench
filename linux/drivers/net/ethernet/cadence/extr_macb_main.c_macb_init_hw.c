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
struct macb_queue {int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  rx_ring_dma; } ;
struct macb {scalar_t__ phy_interface; int caps; unsigned int num_queues; int hw_dma_cap; int rx_intr_mask; struct macb_queue* queues; int /*<<< orphan*/  rx_frm_len_mask; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ jumbo_max_len; TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIG ; 
 int /*<<< orphan*/  CAF ; 
 int /*<<< orphan*/  DRFCS ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int GEM_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HRESP ; 
 int HW_DMA_CAP_64B ; 
 int /*<<< orphan*/  IER ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  JFRAME ; 
 int /*<<< orphan*/  JML ; 
 int MACB_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int MACB_CAPS_JUMBO ; 
 int /*<<< orphan*/  MACB_RX_FRMLEN_MASK ; 
 int /*<<< orphan*/  MACB_RX_JFRMLEN_MASK ; 
 int MACB_TX_INT_FLAGS ; 
 int /*<<< orphan*/  NBC ; 
 int /*<<< orphan*/  NCFGR ; 
 int /*<<< orphan*/  NCR ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  PAE ; 
 int /*<<< orphan*/  PCSSEL ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  RBOF ; 
 int /*<<< orphan*/  RBQP ; 
 int /*<<< orphan*/  RBQPH ; 
 int /*<<< orphan*/  RE ; 
 int /*<<< orphan*/  RXCOEN ; 
 int /*<<< orphan*/  SGMIIEN ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  TBQP ; 
 int /*<<< orphan*/  TBQPH ; 
 int /*<<< orphan*/  TE ; 
 int /*<<< orphan*/  gem_writel (struct macb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_configure_dma (struct macb*) ; 
 int macb_dbw (struct macb*) ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 int macb_mdc_clk_div (struct macb*) ; 
 int macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_reset_hw (struct macb*) ; 
 int /*<<< orphan*/  macb_set_hwaddr (struct macb*) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_writel (struct macb_queue*,int /*<<< orphan*/ ,int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macb_init_hw(struct macb *bp)
{
	struct macb_queue *queue;
	unsigned int q;

	u32 config;

	macb_reset_hw(bp);
	macb_set_hwaddr(bp);

	config = macb_mdc_clk_div(bp);
	if (bp->phy_interface == PHY_INTERFACE_MODE_SGMII)
		config |= GEM_BIT(SGMIIEN) | GEM_BIT(PCSSEL);
	config |= MACB_BF(RBOF, NET_IP_ALIGN);	/* Make eth data aligned */
	config |= MACB_BIT(PAE);		/* PAuse Enable */
	config |= MACB_BIT(DRFCS);		/* Discard Rx FCS */
	if (bp->caps & MACB_CAPS_JUMBO)
		config |= MACB_BIT(JFRAME);	/* Enable jumbo frames */
	else
		config |= MACB_BIT(BIG);	/* Receive oversized frames */
	if (bp->dev->flags & IFF_PROMISC)
		config |= MACB_BIT(CAF);	/* Copy All Frames */
	else if (macb_is_gem(bp) && bp->dev->features & NETIF_F_RXCSUM)
		config |= GEM_BIT(RXCOEN);
	if (!(bp->dev->flags & IFF_BROADCAST))
		config |= MACB_BIT(NBC);	/* No BroadCast */
	config |= macb_dbw(bp);
	macb_writel(bp, NCFGR, config);
	if ((bp->caps & MACB_CAPS_JUMBO) && bp->jumbo_max_len)
		gem_writel(bp, JML, bp->jumbo_max_len);
	bp->speed = SPEED_10;
	bp->duplex = DUPLEX_HALF;
	bp->rx_frm_len_mask = MACB_RX_FRMLEN_MASK;
	if (bp->caps & MACB_CAPS_JUMBO)
		bp->rx_frm_len_mask = MACB_RX_JFRMLEN_MASK;

	macb_configure_dma(bp);

	/* Initialize TX and RX buffers */
	for (q = 0, queue = bp->queues; q < bp->num_queues; ++q, ++queue) {
		queue_writel(queue, RBQP, lower_32_bits(queue->rx_ring_dma));
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (bp->hw_dma_cap & HW_DMA_CAP_64B)
			queue_writel(queue, RBQPH, upper_32_bits(queue->rx_ring_dma));
#endif
		queue_writel(queue, TBQP, lower_32_bits(queue->tx_ring_dma));
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		if (bp->hw_dma_cap & HW_DMA_CAP_64B)
			queue_writel(queue, TBQPH, upper_32_bits(queue->tx_ring_dma));
#endif

		/* Enable interrupts */
		queue_writel(queue, IER,
			     bp->rx_intr_mask |
			     MACB_TX_INT_FLAGS |
			     MACB_BIT(HRESP));
	}

	/* Enable TX and RX */
	macb_writel(bp, NCR, macb_readl(bp, NCR) | MACB_BIT(RE) | MACB_BIT(TE));
}