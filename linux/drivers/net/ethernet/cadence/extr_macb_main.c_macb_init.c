#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int hw_features; int features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct macb_queue {int /*<<< orphan*/  tx_error_task; int /*<<< orphan*/  irq; int /*<<< orphan*/  RBQPH; int /*<<< orphan*/  TBQPH; int /*<<< orphan*/  RBQP; int /*<<< orphan*/  TBQP; int /*<<< orphan*/  IMR; int /*<<< orphan*/  IDR; int /*<<< orphan*/  IER; int /*<<< orphan*/  ISR; int /*<<< orphan*/  RBQS; int /*<<< orphan*/  napi; struct macb* bp; } ;
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  mog_rx; int /*<<< orphan*/  mog_init_rings; int /*<<< orphan*/  mog_free_rx_buffers; int /*<<< orphan*/  mog_alloc_rx_buffers; } ;
struct macb {int queue_mask; int hw_dma_cap; int caps; scalar_t__ max_tuples; scalar_t__ phy_interface; int /*<<< orphan*/  rx_fs_lock; TYPE_1__ rx_fs_list; TYPE_2__ macbgem_ops; int /*<<< orphan*/  max_tx_length; struct macb_queue* queues; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  tx_ring_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKEN ; 
 int /*<<< orphan*/  DCFG6 ; 
 int /*<<< orphan*/  DCFG8 ; 
 int /*<<< orphan*/  DEFAULT_RX_RING_SIZE ; 
 int /*<<< orphan*/  DEFAULT_TX_RING_SIZE ; 
 int /*<<< orphan*/  ETHT ; 
 int /*<<< orphan*/  ETHTCMP ; 
 scalar_t__ ETH_P_IP ; 
 int GEM_BFEXT (int /*<<< orphan*/ ,int) ; 
 int GEM_BFINS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GEM_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_IDR (unsigned int) ; 
 int /*<<< orphan*/  GEM_IER (unsigned int) ; 
 int /*<<< orphan*/  GEM_IMR (unsigned int) ; 
 int /*<<< orphan*/  GEM_ISR (unsigned int) ; 
 int /*<<< orphan*/  GEM_MAX_TX_LEN ; 
 int /*<<< orphan*/  GEM_RBQP (unsigned int) ; 
 int /*<<< orphan*/  GEM_RBQPH (unsigned int) ; 
 int /*<<< orphan*/  GEM_RBQS (unsigned int) ; 
 int /*<<< orphan*/  GEM_TBQP (unsigned int) ; 
 int /*<<< orphan*/  GEM_TBQPH (unsigned int) ; 
 int HW_DMA_CAP_64B ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int MACB_BIT (int /*<<< orphan*/ ) ; 
 int MACB_CAPS_FIFO_MODE ; 
 int MACB_CAPS_SG_DISABLED ; 
 int MACB_CAPS_USRIO_DEFAULT_IS_MII_GMII ; 
 int MACB_CAPS_USRIO_DISABLED ; 
 int MACB_CAPS_USRIO_HAS_CLKEN ; 
 int /*<<< orphan*/  MACB_IDR ; 
 int /*<<< orphan*/  MACB_IER ; 
 int /*<<< orphan*/  MACB_IMR ; 
 int /*<<< orphan*/  MACB_ISR ; 
 unsigned int MACB_MAX_QUEUES ; 
 int /*<<< orphan*/  MACB_MAX_TX_LEN ; 
 int MACB_NETIF_LSO ; 
 int /*<<< orphan*/  MACB_RBQP ; 
 int /*<<< orphan*/  MACB_RBQPH ; 
 int /*<<< orphan*/  MACB_TBQP ; 
 int /*<<< orphan*/  MACB_TBQPH ; 
 int /*<<< orphan*/  MII ; 
 int /*<<< orphan*/  NAPI_POLL_WEIGHT ; 
 int /*<<< orphan*/  NCFGR ; 
 int NETIF_F_HW_CSUM ; 
 int NETIF_F_NTUPLE ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  PBUF_LSO ; 
 int /*<<< orphan*/  PCSSEL ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  RGMII ; 
 int /*<<< orphan*/  RMII ; 
 int /*<<< orphan*/  SCR2CMP ; 
 int /*<<< orphan*/  SCR2ETH ; 
 int /*<<< orphan*/  SCRT2_ETHT ; 
 int /*<<< orphan*/  SGMIIEN ; 
 int /*<<< orphan*/  T2SCR ; 
 int /*<<< orphan*/  USRIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct macb_queue*) ; 
 int /*<<< orphan*/  gem_alloc_rx_buffers ; 
 int /*<<< orphan*/  gem_ethtool_ops ; 
 int /*<<< orphan*/  gem_free_rx_buffers ; 
 int /*<<< orphan*/  gem_init_rings ; 
 int gem_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gem_rx ; 
 int /*<<< orphan*/  gem_writel_n (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  macb_alloc_rx_buffers ; 
 int macb_dbw (struct macb*) ; 
 int /*<<< orphan*/  macb_ethtool_ops ; 
 int /*<<< orphan*/  macb_free_rx_buffers ; 
 int /*<<< orphan*/  macb_init_rings ; 
 int /*<<< orphan*/  macb_interrupt ; 
 scalar_t__ macb_is_gem (struct macb*) ; 
 int macb_mdc_clk_div (struct macb*) ; 
 int /*<<< orphan*/  macb_netdev_ops ; 
 int /*<<< orphan*/  macb_or_gem_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  macb_poll ; 
 int /*<<< orphan*/  macb_rx ; 
 int /*<<< orphan*/  macb_tx_error_task ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (int,int) ; 
 struct macb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int macb_init(struct platform_device *pdev)
{
	struct net_device *dev = platform_get_drvdata(pdev);
	unsigned int hw_q, q;
	struct macb *bp = netdev_priv(dev);
	struct macb_queue *queue;
	int err;
	u32 val, reg;

	bp->tx_ring_size = DEFAULT_TX_RING_SIZE;
	bp->rx_ring_size = DEFAULT_RX_RING_SIZE;

	/* set the queue register mapping once for all: queue0 has a special
	 * register mapping but we don't want to test the queue index then
	 * compute the corresponding register offset at run time.
	 */
	for (hw_q = 0, q = 0; hw_q < MACB_MAX_QUEUES; ++hw_q) {
		if (!(bp->queue_mask & (1 << hw_q)))
			continue;

		queue = &bp->queues[q];
		queue->bp = bp;
		netif_napi_add(dev, &queue->napi, macb_poll, NAPI_POLL_WEIGHT);
		if (hw_q) {
			queue->ISR  = GEM_ISR(hw_q - 1);
			queue->IER  = GEM_IER(hw_q - 1);
			queue->IDR  = GEM_IDR(hw_q - 1);
			queue->IMR  = GEM_IMR(hw_q - 1);
			queue->TBQP = GEM_TBQP(hw_q - 1);
			queue->RBQP = GEM_RBQP(hw_q - 1);
			queue->RBQS = GEM_RBQS(hw_q - 1);
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
			if (bp->hw_dma_cap & HW_DMA_CAP_64B) {
				queue->TBQPH = GEM_TBQPH(hw_q - 1);
				queue->RBQPH = GEM_RBQPH(hw_q - 1);
			}
#endif
		} else {
			/* queue0 uses legacy registers */
			queue->ISR  = MACB_ISR;
			queue->IER  = MACB_IER;
			queue->IDR  = MACB_IDR;
			queue->IMR  = MACB_IMR;
			queue->TBQP = MACB_TBQP;
			queue->RBQP = MACB_RBQP;
#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
			if (bp->hw_dma_cap & HW_DMA_CAP_64B) {
				queue->TBQPH = MACB_TBQPH;
				queue->RBQPH = MACB_RBQPH;
			}
#endif
		}

		/* get irq: here we use the linux queue index, not the hardware
		 * queue index. the queue irq definitions in the device tree
		 * must remove the optional gaps that could exist in the
		 * hardware queue mask.
		 */
		queue->irq = platform_get_irq(pdev, q);
		err = devm_request_irq(&pdev->dev, queue->irq, macb_interrupt,
				       IRQF_SHARED, dev->name, queue);
		if (err) {
			dev_err(&pdev->dev,
				"Unable to request IRQ %d (error %d)\n",
				queue->irq, err);
			return err;
		}

		INIT_WORK(&queue->tx_error_task, macb_tx_error_task);
		q++;
	}

	dev->netdev_ops = &macb_netdev_ops;

	/* setup appropriated routines according to adapter type */
	if (macb_is_gem(bp)) {
		bp->max_tx_length = GEM_MAX_TX_LEN;
		bp->macbgem_ops.mog_alloc_rx_buffers = gem_alloc_rx_buffers;
		bp->macbgem_ops.mog_free_rx_buffers = gem_free_rx_buffers;
		bp->macbgem_ops.mog_init_rings = gem_init_rings;
		bp->macbgem_ops.mog_rx = gem_rx;
		dev->ethtool_ops = &gem_ethtool_ops;
	} else {
		bp->max_tx_length = MACB_MAX_TX_LEN;
		bp->macbgem_ops.mog_alloc_rx_buffers = macb_alloc_rx_buffers;
		bp->macbgem_ops.mog_free_rx_buffers = macb_free_rx_buffers;
		bp->macbgem_ops.mog_init_rings = macb_init_rings;
		bp->macbgem_ops.mog_rx = macb_rx;
		dev->ethtool_ops = &macb_ethtool_ops;
	}

	/* Set features */
	dev->hw_features = NETIF_F_SG;

	/* Check LSO capability */
	if (GEM_BFEXT(PBUF_LSO, gem_readl(bp, DCFG6)))
		dev->hw_features |= MACB_NETIF_LSO;

	/* Checksum offload is only available on gem with packet buffer */
	if (macb_is_gem(bp) && !(bp->caps & MACB_CAPS_FIFO_MODE))
		dev->hw_features |= NETIF_F_HW_CSUM | NETIF_F_RXCSUM;
	if (bp->caps & MACB_CAPS_SG_DISABLED)
		dev->hw_features &= ~NETIF_F_SG;
	dev->features = dev->hw_features;

	/* Check RX Flow Filters support.
	 * Max Rx flows set by availability of screeners & compare regs:
	 * each 4-tuple define requires 1 T2 screener reg + 3 compare regs
	 */
	reg = gem_readl(bp, DCFG8);
	bp->max_tuples = min((GEM_BFEXT(SCR2CMP, reg) / 3),
			GEM_BFEXT(T2SCR, reg));
	if (bp->max_tuples > 0) {
		/* also needs one ethtype match to check IPv4 */
		if (GEM_BFEXT(SCR2ETH, reg) > 0) {
			/* program this reg now */
			reg = 0;
			reg = GEM_BFINS(ETHTCMP, (uint16_t)ETH_P_IP, reg);
			gem_writel_n(bp, ETHT, SCRT2_ETHT, reg);
			/* Filtering is supported in hw but don't enable it in kernel now */
			dev->hw_features |= NETIF_F_NTUPLE;
			/* init Rx flow definitions */
			INIT_LIST_HEAD(&bp->rx_fs_list.list);
			bp->rx_fs_list.count = 0;
			spin_lock_init(&bp->rx_fs_lock);
		} else
			bp->max_tuples = 0;
	}

	if (!(bp->caps & MACB_CAPS_USRIO_DISABLED)) {
		val = 0;
		if (bp->phy_interface == PHY_INTERFACE_MODE_RGMII)
			val = GEM_BIT(RGMII);
		else if (bp->phy_interface == PHY_INTERFACE_MODE_RMII &&
			 (bp->caps & MACB_CAPS_USRIO_DEFAULT_IS_MII_GMII))
			val = MACB_BIT(RMII);
		else if (!(bp->caps & MACB_CAPS_USRIO_DEFAULT_IS_MII_GMII))
			val = MACB_BIT(MII);

		if (bp->caps & MACB_CAPS_USRIO_HAS_CLKEN)
			val |= MACB_BIT(CLKEN);

		macb_or_gem_writel(bp, USRIO, val);
	}

	/* Set MII management clock divider */
	val = macb_mdc_clk_div(bp);
	val |= macb_dbw(bp);
	if (bp->phy_interface == PHY_INTERFACE_MODE_SGMII)
		val |= GEM_BIT(SGMIIEN) | GEM_BIT(PCSSEL);
	macb_writel(bp, NCFGR, val);

	return 0;
}