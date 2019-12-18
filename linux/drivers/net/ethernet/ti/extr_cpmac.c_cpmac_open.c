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
typedef  void* u32 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct net_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  phydev; int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct cpmac_priv {size_t ring_size; int /*<<< orphan*/  regs; scalar_t__ dma_ring; struct cpmac_desc* desc_ring; struct cpmac_desc* rx_head; int /*<<< orphan*/  napi; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  reset_pending; int /*<<< orphan*/  pdev; } ;
struct cpmac_desc {struct sk_buff* skb; scalar_t__ data_mapping; void* hw_next; struct cpmac_desc* prev; scalar_t__ mapping; struct cpmac_desc* next; int /*<<< orphan*/  dataflags; int /*<<< orphan*/  buflen; void* hw_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPMAC_OWN ; 
 size_t CPMAC_QUEUES ; 
 int /*<<< orphan*/  CPMAC_SKB_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpmac_hw_error ; 
 int /*<<< orphan*/  cpmac_hw_start (struct net_device*) ; 
 int /*<<< orphan*/  cpmac_irq ; 
 struct cpmac_desc* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct cpmac_desc*,scalar_t__) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct cpmac_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_drv (struct cpmac_priv*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cpmac_open(struct net_device *dev)
{
	int i, size, res;
	struct cpmac_priv *priv = netdev_priv(dev);
	struct resource *mem;
	struct cpmac_desc *desc;
	struct sk_buff *skb;

	mem = platform_get_resource_byname(priv->pdev, IORESOURCE_MEM, "regs");
	if (!request_mem_region(mem->start, resource_size(mem), dev->name)) {
		if (netif_msg_drv(priv))
			netdev_err(dev, "failed to request registers\n");

		res = -ENXIO;
		goto fail_reserve;
	}

	priv->regs = ioremap(mem->start, resource_size(mem));
	if (!priv->regs) {
		if (netif_msg_drv(priv))
			netdev_err(dev, "failed to remap registers\n");

		res = -ENXIO;
		goto fail_remap;
	}

	size = priv->ring_size + CPMAC_QUEUES;
	priv->desc_ring = dma_alloc_coherent(&dev->dev,
					     sizeof(struct cpmac_desc) * size,
					     &priv->dma_ring,
					     GFP_KERNEL);
	if (!priv->desc_ring) {
		res = -ENOMEM;
		goto fail_alloc;
	}

	for (i = 0; i < size; i++)
		priv->desc_ring[i].mapping = priv->dma_ring + sizeof(*desc) * i;

	priv->rx_head = &priv->desc_ring[CPMAC_QUEUES];
	for (i = 0, desc = priv->rx_head; i < priv->ring_size; i++, desc++) {
		skb = netdev_alloc_skb_ip_align(dev, CPMAC_SKB_SIZE);
		if (unlikely(!skb)) {
			res = -ENOMEM;
			goto fail_desc;
		}
		desc->skb = skb;
		desc->data_mapping = dma_map_single(&dev->dev, skb->data,
						    CPMAC_SKB_SIZE,
						    DMA_FROM_DEVICE);
		desc->hw_data = (u32)desc->data_mapping;
		desc->buflen = CPMAC_SKB_SIZE;
		desc->dataflags = CPMAC_OWN;
		desc->next = &priv->rx_head[(i + 1) % priv->ring_size];
		desc->next->prev = desc;
		desc->hw_next = (u32)desc->next->mapping;
	}

	priv->rx_head->prev->hw_next = (u32)0;

	res = request_irq(dev->irq, cpmac_irq, IRQF_SHARED, dev->name, dev);
	if (res) {
		if (netif_msg_drv(priv))
			netdev_err(dev, "failed to obtain irq\n");

		goto fail_irq;
	}

	atomic_set(&priv->reset_pending, 0);
	INIT_WORK(&priv->reset_work, cpmac_hw_error);
	cpmac_hw_start(dev);

	napi_enable(&priv->napi);
	phy_start(dev->phydev);

	return 0;

fail_irq:
fail_desc:
	for (i = 0; i < priv->ring_size; i++) {
		if (priv->rx_head[i].skb) {
			dma_unmap_single(&dev->dev,
					 priv->rx_head[i].data_mapping,
					 CPMAC_SKB_SIZE,
					 DMA_FROM_DEVICE);
			kfree_skb(priv->rx_head[i].skb);
		}
	}
	dma_free_coherent(&dev->dev, sizeof(struct cpmac_desc) * size,
			  priv->desc_ring, priv->dma_ring);

fail_alloc:
	iounmap(priv->regs);

fail_remap:
	release_mem_region(mem->start, resource_size(mem));

fail_reserve:
	return res;
}