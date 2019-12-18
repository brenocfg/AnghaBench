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
typedef  int u32 ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct sk_buff {int dummy; } ;
struct phy_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct bcm_enet_priv {int old_duplex; int old_pause; int rx_ring_size; int rx_desc_dma; unsigned int rx_desc_alloc_size; int tx_ring_size; int tx_desc_dma; unsigned int tx_desc_alloc_size; int tx_desc_count; int hw_mtu; int dma_maxburst; int dma_chan_en_mask; int dma_chan_int_mask; int /*<<< orphan*/  irq_rx; int /*<<< orphan*/  irq_tx; struct bcm_enet_desc* rx_desc_cpu; struct bcm_enet_desc* tx_desc_cpu; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  rx_skb_size; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  napi; scalar_t__ dma_has_sram; scalar_t__ rx_curr_desc; scalar_t__ rx_dirty_desc; scalar_t__ rx_desc_count; int /*<<< orphan*/  tx_lock; scalar_t__ tx_curr_desc; scalar_t__ tx_dirty_desc; scalar_t__ old_link; int /*<<< orphan*/  pause_auto; int /*<<< orphan*/  pause_rx; int /*<<< orphan*/  phy_id; TYPE_2__* mii_bus; scalar_t__ has_phy; TYPE_1__* pdev; } ;
struct bcm_enet_desc {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  phy_id ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int BCMENET_TX_FIFO_TRESH ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ENETDMAC_BUFALLOC ; 
 int /*<<< orphan*/  ENETDMAC_CHANCFG ; 
 int /*<<< orphan*/  ENETDMAC_FC ; 
 int /*<<< orphan*/  ENETDMAC_IR ; 
 int /*<<< orphan*/  ENETDMAC_IRMASK ; 
 int /*<<< orphan*/  ENETDMAC_LEN ; 
 int /*<<< orphan*/  ENETDMAC_MAXBURST ; 
 int /*<<< orphan*/  ENETDMAC_RSTART ; 
 int /*<<< orphan*/  ENETDMAS_RSTART_REG ; 
 int /*<<< orphan*/  ENETDMAS_SRAM2_REG ; 
 int /*<<< orphan*/  ENETDMAS_SRAM3_REG ; 
 int /*<<< orphan*/  ENETDMAS_SRAM4_REG ; 
 int ENETDMA_BUFALLOC_FORCE_MASK ; 
 int /*<<< orphan*/  ENETDMA_BUFALLOC_REG (int /*<<< orphan*/ ) ; 
 int ENETDMA_CFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMA_CFG_REG ; 
 int /*<<< orphan*/  ENETDMA_FLOWCH_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENETDMA_FLOWCL_REG (int /*<<< orphan*/ ) ; 
 int ENET_CTL_ENABLE_MASK ; 
 int /*<<< orphan*/  ENET_CTL_REG ; 
 int /*<<< orphan*/  ENET_IRMASK_REG ; 
 int ENET_IR_MIB ; 
 int /*<<< orphan*/  ENET_IR_REG ; 
 int /*<<< orphan*/  ENET_PMH_REG (int) ; 
 int /*<<< orphan*/  ENET_PML_REG (int) ; 
 int /*<<< orphan*/  ENET_RXMAXLEN_REG ; 
 int /*<<< orphan*/  ENET_TXMAXLEN_REG ; 
 int /*<<< orphan*/  ENET_TXWMARK_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  bcm_enet_adjust_link (struct net_device*) ; 
 int /*<<< orphan*/  bcm_enet_adjust_phy_link ; 
 int /*<<< orphan*/  bcm_enet_isr_dma ; 
 int /*<<< orphan*/  bcm_enet_isr_mac ; 
 scalar_t__ bcm_enet_refill_rx (struct net_device*) ; 
 int /*<<< orphan*/  bcm_enet_set_mac_address (struct net_device*,struct sockaddr*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* dma_alloc_coherent (struct device*,unsigned int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,unsigned int,struct bcm_enet_desc*,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dma_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dmac_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dmas_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int enet_readl (struct bcm_enet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_writel (struct bcm_enet_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_attached_info (struct phy_device*) ; 
 struct phy_device* phy_connect (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_disconnect (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_max_speed (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_set_sym_pause (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (struct phy_device*) ; 
 int /*<<< orphan*/  phy_support_sym_pause (struct phy_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int bcm_enet_open(struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct sockaddr addr;
	struct device *kdev;
	struct phy_device *phydev;
	int i, ret;
	unsigned int size;
	char phy_id[MII_BUS_ID_SIZE + 3];
	void *p;
	u32 val;

	priv = netdev_priv(dev);
	kdev = &priv->pdev->dev;

	if (priv->has_phy) {
		/* connect to PHY */
		snprintf(phy_id, sizeof(phy_id), PHY_ID_FMT,
			 priv->mii_bus->id, priv->phy_id);

		phydev = phy_connect(dev, phy_id, bcm_enet_adjust_phy_link,
				     PHY_INTERFACE_MODE_MII);

		if (IS_ERR(phydev)) {
			dev_err(kdev, "could not attach to PHY\n");
			return PTR_ERR(phydev);
		}

		/* mask with MAC supported features */
		phy_support_sym_pause(phydev);
		phy_set_max_speed(phydev, SPEED_100);
		phy_set_sym_pause(phydev, priv->pause_rx, priv->pause_rx,
				  priv->pause_auto);

		phy_attached_info(phydev);

		priv->old_link = 0;
		priv->old_duplex = -1;
		priv->old_pause = -1;
	} else {
		phydev = NULL;
	}

	/* mask all interrupts and request them */
	enet_writel(priv, 0, ENET_IRMASK_REG);
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_writel(priv, 0, ENETDMAC_IRMASK, priv->tx_chan);

	ret = request_irq(dev->irq, bcm_enet_isr_mac, 0, dev->name, dev);
	if (ret)
		goto out_phy_disconnect;

	ret = request_irq(priv->irq_rx, bcm_enet_isr_dma, 0,
			  dev->name, dev);
	if (ret)
		goto out_freeirq;

	ret = request_irq(priv->irq_tx, bcm_enet_isr_dma,
			  0, dev->name, dev);
	if (ret)
		goto out_freeirq_rx;

	/* initialize perfect match registers */
	for (i = 0; i < 4; i++) {
		enet_writel(priv, 0, ENET_PML_REG(i));
		enet_writel(priv, 0, ENET_PMH_REG(i));
	}

	/* write device mac address */
	memcpy(addr.sa_data, dev->dev_addr, ETH_ALEN);
	bcm_enet_set_mac_address(dev, &addr);

	/* allocate rx dma ring */
	size = priv->rx_ring_size * sizeof(struct bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->rx_desc_dma, GFP_KERNEL);
	if (!p) {
		ret = -ENOMEM;
		goto out_freeirq_tx;
	}

	priv->rx_desc_alloc_size = size;
	priv->rx_desc_cpu = p;

	/* allocate tx dma ring */
	size = priv->tx_ring_size * sizeof(struct bcm_enet_desc);
	p = dma_alloc_coherent(kdev, size, &priv->tx_desc_dma, GFP_KERNEL);
	if (!p) {
		ret = -ENOMEM;
		goto out_free_rx_ring;
	}

	priv->tx_desc_alloc_size = size;
	priv->tx_desc_cpu = p;

	priv->tx_skb = kcalloc(priv->tx_ring_size, sizeof(struct sk_buff *),
			       GFP_KERNEL);
	if (!priv->tx_skb) {
		ret = -ENOMEM;
		goto out_free_tx_ring;
	}

	priv->tx_desc_count = priv->tx_ring_size;
	priv->tx_dirty_desc = 0;
	priv->tx_curr_desc = 0;
	spin_lock_init(&priv->tx_lock);

	/* init & fill rx ring with skbs */
	priv->rx_skb = kcalloc(priv->rx_ring_size, sizeof(struct sk_buff *),
			       GFP_KERNEL);
	if (!priv->rx_skb) {
		ret = -ENOMEM;
		goto out_free_tx_skb;
	}

	priv->rx_desc_count = 0;
	priv->rx_dirty_desc = 0;
	priv->rx_curr_desc = 0;

	/* initialize flow control buffer allocation */
	if (priv->dma_has_sram)
		enet_dma_writel(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
				ENETDMA_BUFALLOC_REG(priv->rx_chan));
	else
		enet_dmac_writel(priv, ENETDMA_BUFALLOC_FORCE_MASK | 0,
				ENETDMAC_BUFALLOC, priv->rx_chan);

	if (bcm_enet_refill_rx(dev)) {
		dev_err(kdev, "cannot allocate rx skb queue\n");
		ret = -ENOMEM;
		goto out;
	}

	/* write rx & tx ring addresses */
	if (priv->dma_has_sram) {
		enet_dmas_writel(priv, priv->rx_desc_dma,
				 ENETDMAS_RSTART_REG, priv->rx_chan);
		enet_dmas_writel(priv, priv->tx_desc_dma,
			 ENETDMAS_RSTART_REG, priv->tx_chan);
	} else {
		enet_dmac_writel(priv, priv->rx_desc_dma,
				ENETDMAC_RSTART, priv->rx_chan);
		enet_dmac_writel(priv, priv->tx_desc_dma,
				ENETDMAC_RSTART, priv->tx_chan);
	}

	/* clear remaining state ram for rx & tx channel */
	if (priv->dma_has_sram) {
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM2_REG, priv->rx_chan);
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM2_REG, priv->tx_chan);
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM3_REG, priv->rx_chan);
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM3_REG, priv->tx_chan);
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM4_REG, priv->rx_chan);
		enet_dmas_writel(priv, 0, ENETDMAS_SRAM4_REG, priv->tx_chan);
	} else {
		enet_dmac_writel(priv, 0, ENETDMAC_FC, priv->rx_chan);
		enet_dmac_writel(priv, 0, ENETDMAC_FC, priv->tx_chan);
	}

	/* set max rx/tx length */
	enet_writel(priv, priv->hw_mtu, ENET_RXMAXLEN_REG);
	enet_writel(priv, priv->hw_mtu, ENET_TXMAXLEN_REG);

	/* set dma maximum burst len */
	enet_dmac_writel(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->rx_chan);
	enet_dmac_writel(priv, priv->dma_maxburst,
			 ENETDMAC_MAXBURST, priv->tx_chan);

	/* set correct transmit fifo watermark */
	enet_writel(priv, BCMENET_TX_FIFO_TRESH, ENET_TXWMARK_REG);

	/* set flow control low/high threshold to 1/3 / 2/3 */
	if (priv->dma_has_sram) {
		val = priv->rx_ring_size / 3;
		enet_dma_writel(priv, val, ENETDMA_FLOWCL_REG(priv->rx_chan));
		val = (priv->rx_ring_size * 2) / 3;
		enet_dma_writel(priv, val, ENETDMA_FLOWCH_REG(priv->rx_chan));
	} else {
		enet_dmac_writel(priv, 5, ENETDMAC_FC, priv->rx_chan);
		enet_dmac_writel(priv, priv->rx_ring_size, ENETDMAC_LEN, priv->rx_chan);
		enet_dmac_writel(priv, priv->tx_ring_size, ENETDMAC_LEN, priv->tx_chan);
	}

	/* all set, enable mac and interrupts, start dma engine and
	 * kick rx dma channel */
	wmb();
	val = enet_readl(priv, ENET_CTL_REG);
	val |= ENET_CTL_ENABLE_MASK;
	enet_writel(priv, val, ENET_CTL_REG);
	if (priv->dma_has_sram)
		enet_dma_writel(priv, ENETDMA_CFG_EN_MASK, ENETDMA_CFG_REG);
	enet_dmac_writel(priv, priv->dma_chan_en_mask,
			 ENETDMAC_CHANCFG, priv->rx_chan);

	/* watch "mib counters about to overflow" interrupt */
	enet_writel(priv, ENET_IR_MIB, ENET_IR_REG);
	enet_writel(priv, ENET_IR_MIB, ENET_IRMASK_REG);

	/* watch "packet transferred" interrupt in rx and tx */
	enet_dmac_writel(priv, priv->dma_chan_int_mask,
			 ENETDMAC_IR, priv->rx_chan);
	enet_dmac_writel(priv, priv->dma_chan_int_mask,
			 ENETDMAC_IR, priv->tx_chan);

	/* make sure we enable napi before rx interrupt  */
	napi_enable(&priv->napi);

	enet_dmac_writel(priv, priv->dma_chan_int_mask,
			 ENETDMAC_IRMASK, priv->rx_chan);
	enet_dmac_writel(priv, priv->dma_chan_int_mask,
			 ENETDMAC_IRMASK, priv->tx_chan);

	if (phydev)
		phy_start(phydev);
	else
		bcm_enet_adjust_link(dev);

	netif_start_queue(dev);
	return 0;

out:
	for (i = 0; i < priv->rx_ring_size; i++) {
		struct bcm_enet_desc *desc;

		if (!priv->rx_skb[i])
			continue;

		desc = &priv->rx_desc_cpu[i];
		dma_unmap_single(kdev, desc->address, priv->rx_skb_size,
				 DMA_FROM_DEVICE);
		kfree_skb(priv->rx_skb[i]);
	}
	kfree(priv->rx_skb);

out_free_tx_skb:
	kfree(priv->tx_skb);

out_free_tx_ring:
	dma_free_coherent(kdev, priv->tx_desc_alloc_size,
			  priv->tx_desc_cpu, priv->tx_desc_dma);

out_free_rx_ring:
	dma_free_coherent(kdev, priv->rx_desc_alloc_size,
			  priv->rx_desc_cpu, priv->rx_desc_dma);

out_freeirq_tx:
	free_irq(priv->irq_tx, dev);

out_freeirq_rx:
	free_irq(priv->irq_rx, dev);

out_freeirq:
	free_irq(dev->irq, dev);

out_phy_disconnect:
	if (phydev)
		phy_disconnect(phydev);

	return ret;
}