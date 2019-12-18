#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int start; } ;
struct skge_port {scalar_t__ rx_buf_size; TYPE_3__* hw; TYPE_1__ rx_ring; int /*<<< orphan*/  netdev; } ;
struct skge_element {struct sk_buff* skb; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_length_errors; } ;
struct net_device {int features; TYPE_2__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int BMU_BBC ; 
 int BMU_EOF ; 
 int BMU_STF ; 
 int /*<<< orphan*/  CHECKSUM_COMPLETE ; 
 int GMR_FS_CRC_ERR ; 
 int GMR_FS_FRAGMENT ; 
 int GMR_FS_LONG_ERR ; 
 int GMR_FS_UN_SIZE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ RX_COPY_THRESHOLD ; 
 int XMR_FS_FCS_ERR ; 
 int XMR_FS_FRA_ERR ; 
 int XMR_FS_LNG_ERR ; 
 int XMR_FS_RUNT ; 
 scalar_t__ bad_phy_status (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ is_genesis (TYPE_3__*) ; 
 int /*<<< orphan*/  le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct skge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct skge_element*,int,int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phy_length (TYPE_3__*,int) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skge_rx_reuse (struct skge_element*,scalar_t__) ; 
 scalar_t__ skge_rx_setup (struct skge_port*,struct skge_element*,struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *skge_rx_get(struct net_device *dev,
				   struct skge_element *e,
				   u32 control, u32 status, u16 csum)
{
	struct skge_port *skge = netdev_priv(dev);
	struct sk_buff *skb;
	u16 len = control & BMU_BBC;

	netif_printk(skge, rx_status, KERN_DEBUG, skge->netdev,
		     "rx slot %td status 0x%x len %d\n",
		     e - skge->rx_ring.start, status, len);

	if (len > skge->rx_buf_size)
		goto error;

	if ((control & (BMU_EOF|BMU_STF)) != (BMU_STF|BMU_EOF))
		goto error;

	if (bad_phy_status(skge->hw, status))
		goto error;

	if (phy_length(skge->hw, status) != len)
		goto error;

	if (len < RX_COPY_THRESHOLD) {
		skb = netdev_alloc_skb_ip_align(dev, len);
		if (!skb)
			goto resubmit;

		pci_dma_sync_single_for_cpu(skge->hw->pdev,
					    dma_unmap_addr(e, mapaddr),
					    dma_unmap_len(e, maplen),
					    PCI_DMA_FROMDEVICE);
		skb_copy_from_linear_data(e->skb, skb->data, len);
		pci_dma_sync_single_for_device(skge->hw->pdev,
					       dma_unmap_addr(e, mapaddr),
					       dma_unmap_len(e, maplen),
					       PCI_DMA_FROMDEVICE);
		skge_rx_reuse(e, skge->rx_buf_size);
	} else {
		struct skge_element ee;
		struct sk_buff *nskb;

		nskb = netdev_alloc_skb_ip_align(dev, skge->rx_buf_size);
		if (!nskb)
			goto resubmit;

		ee = *e;

		skb = ee.skb;
		prefetch(skb->data);

		if (skge_rx_setup(skge, e, nskb, skge->rx_buf_size) < 0) {
			dev_kfree_skb(nskb);
			goto resubmit;
		}

		pci_unmap_single(skge->hw->pdev,
				 dma_unmap_addr(&ee, mapaddr),
				 dma_unmap_len(&ee, maplen),
				 PCI_DMA_FROMDEVICE);
	}

	skb_put(skb, len);

	if (dev->features & NETIF_F_RXCSUM) {
		skb->csum = le16_to_cpu(csum);
		skb->ip_summed = CHECKSUM_COMPLETE;
	}

	skb->protocol = eth_type_trans(skb, dev);

	return skb;
error:

	netif_printk(skge, rx_err, KERN_DEBUG, skge->netdev,
		     "rx err, slot %td control 0x%x status 0x%x\n",
		     e - skge->rx_ring.start, control, status);

	if (is_genesis(skge->hw)) {
		if (status & (XMR_FS_RUNT|XMR_FS_LNG_ERR))
			dev->stats.rx_length_errors++;
		if (status & XMR_FS_FRA_ERR)
			dev->stats.rx_frame_errors++;
		if (status & XMR_FS_FCS_ERR)
			dev->stats.rx_crc_errors++;
	} else {
		if (status & (GMR_FS_LONG_ERR|GMR_FS_UN_SIZE))
			dev->stats.rx_length_errors++;
		if (status & GMR_FS_FRAGMENT)
			dev->stats.rx_frame_errors++;
		if (status & GMR_FS_CRC_ERR)
			dev->stats.rx_crc_errors++;
	}

resubmit:
	skge_rx_reuse(e, skge->rx_buf_size);
	return NULL;
}