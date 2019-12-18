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
struct slic_tx_queue {size_t put_idx; int /*<<< orphan*/  len; struct slic_tx_buffer* txbuffs; } ;
struct slic_tx_desc {void* len; void* paddrh; void* paddrl; void* totlen; } ;
struct slic_tx_buffer {int /*<<< orphan*/  desc_paddr; struct slic_tx_desc* desc; struct sk_buff* skb; } ;
struct slic_device {TYPE_1__* pdev; struct slic_tx_queue txq; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ SLIC_MAX_REQ_TX_DESCS ; 
 int /*<<< orphan*/  SLIC_REG_CBAR ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct slic_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct slic_tx_buffer*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_addr ; 
 int /*<<< orphan*/  map_len ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct slic_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int skb_headlen (struct sk_buff*) ; 
 scalar_t__ slic_get_free_tx_descs (struct slic_tx_queue*) ; 
 size_t slic_next_queue_idx (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t slic_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct slic_device *sdev = netdev_priv(dev);
	struct slic_tx_queue *txq = &sdev->txq;
	struct slic_tx_buffer *buff;
	struct slic_tx_desc *desc;
	dma_addr_t paddr;
	u32 cbar_val;
	u32 maplen;

	if (unlikely(slic_get_free_tx_descs(txq) < SLIC_MAX_REQ_TX_DESCS)) {
		netdev_err(dev, "BUG! not enough tx LEs left: %u\n",
			   slic_get_free_tx_descs(txq));
		return NETDEV_TX_BUSY;
	}

	maplen = skb_headlen(skb);
	paddr = dma_map_single(&sdev->pdev->dev, skb->data, maplen,
			       DMA_TO_DEVICE);
	if (dma_mapping_error(&sdev->pdev->dev, paddr)) {
		netdev_err(dev, "failed to map tx buffer\n");
		goto drop_skb;
	}

	buff = &txq->txbuffs[txq->put_idx];
	buff->skb = skb;
	dma_unmap_addr_set(buff, map_addr, paddr);
	dma_unmap_len_set(buff, map_len, maplen);

	desc = buff->desc;
	desc->totlen = cpu_to_le32(maplen);
	desc->paddrl = cpu_to_le32(lower_32_bits(paddr));
	desc->paddrh = cpu_to_le32(upper_32_bits(paddr));
	desc->len = cpu_to_le32(maplen);

	txq->put_idx = slic_next_queue_idx(txq->put_idx, txq->len);

	cbar_val = lower_32_bits(buff->desc_paddr) | 1;
	/* complete writes to RAM and DMA before hardware is informed */
	wmb();

	slic_write(sdev, SLIC_REG_CBAR, cbar_val);

	if (slic_get_free_tx_descs(txq) < SLIC_MAX_REQ_TX_DESCS)
		netif_stop_queue(dev);

	return NETDEV_TX_OK;
drop_skb:
	dev_kfree_skb_any(skb);

	return NETDEV_TX_OK;
}