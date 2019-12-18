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
typedef  size_t u32 ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct p54p_ring_control {void** host_idx; struct p54p_desc* tx_data; } ;
struct p54p_priv {int /*<<< orphan*/  lock; struct sk_buff** tx_buf_data; TYPE_1__* pdev; struct p54p_ring_control* ring_control; } ;
struct p54p_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  device_addr; void* host_addr; } ;
struct p54_hdr {int /*<<< orphan*/  req_id; } ;
struct ieee80211_hw {struct p54p_priv* priv; } ;
typedef  size_t dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct p54p_desc*) ; 
 size_t ISL38XX_DEV_INT_UPDATE ; 
 int /*<<< orphan*/  P54P_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P54P_WRITE (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_int ; 
 size_t le32_to_cpu (void*) ; 
 int /*<<< orphan*/  p54_free_skb (struct ieee80211_hw*,struct sk_buff*) ; 
 scalar_t__ pci_dma_mapping_error (TYPE_1__*,size_t) ; 
 size_t pci_map_single (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void p54p_tx(struct ieee80211_hw *dev, struct sk_buff *skb)
{
	unsigned long flags;
	struct p54p_priv *priv = dev->priv;
	struct p54p_ring_control *ring_control = priv->ring_control;
	struct p54p_desc *desc;
	dma_addr_t mapping;
	u32 idx, i;

	spin_lock_irqsave(&priv->lock, flags);
	idx = le32_to_cpu(ring_control->host_idx[1]);
	i = idx % ARRAY_SIZE(ring_control->tx_data);

	mapping = pci_map_single(priv->pdev, skb->data, skb->len,
				 PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(priv->pdev, mapping)) {
		spin_unlock_irqrestore(&priv->lock, flags);
		p54_free_skb(dev, skb);
		dev_err(&priv->pdev->dev, "TX DMA mapping error\n");
		return ;
	}
	priv->tx_buf_data[i] = skb;

	desc = &ring_control->tx_data[i];
	desc->host_addr = cpu_to_le32(mapping);
	desc->device_addr = ((struct p54_hdr *)skb->data)->req_id;
	desc->len = cpu_to_le16(skb->len);
	desc->flags = 0;

	wmb();
	ring_control->host_idx[1] = cpu_to_le32(idx + 1);
	spin_unlock_irqrestore(&priv->lock, flags);

	P54P_WRITE(dev_int, cpu_to_le32(ISL38XX_DEV_INT_UPDATE));
	P54P_READ(dev_int);
}