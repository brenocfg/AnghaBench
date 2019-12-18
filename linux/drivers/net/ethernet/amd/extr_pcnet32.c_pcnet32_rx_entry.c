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
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ len; scalar_t__ data; } ;
struct pcnet32_rx_head {int /*<<< orphan*/  base; int /*<<< orphan*/  msg_length; int /*<<< orphan*/  status; } ;
struct pcnet32_private {int /*<<< orphan*/ * rx_dma_addr; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_frame_errors; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 short PKT_BUF_SIZE ; 
 scalar_t__ PKT_BUF_SKB ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_err (struct pcnet32_private*,int /*<<< orphan*/ ,struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,int /*<<< orphan*/ ) ; 
 short rx_copybreak ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,short) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,short) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pcnet32_rx_entry(struct net_device *dev,
			     struct pcnet32_private *lp,
			     struct pcnet32_rx_head *rxp,
			     int entry)
{
	int status = (short)le16_to_cpu(rxp->status) >> 8;
	int rx_in_place = 0;
	struct sk_buff *skb;
	short pkt_len;

	if (status != 0x03) {	/* There was an error. */
		/*
		 * There is a tricky error noted by John Murphy,
		 * <murf@perftech.com> to Russ Nelson: Even with full-sized
		 * buffers it's possible for a jabber packet to use two
		 * buffers, with only the last correctly noting the error.
		 */
		if (status & 0x01)	/* Only count a general error at the */
			dev->stats.rx_errors++;	/* end of a packet. */
		if (status & 0x20)
			dev->stats.rx_frame_errors++;
		if (status & 0x10)
			dev->stats.rx_over_errors++;
		if (status & 0x08)
			dev->stats.rx_crc_errors++;
		if (status & 0x04)
			dev->stats.rx_fifo_errors++;
		return;
	}

	pkt_len = (le32_to_cpu(rxp->msg_length) & 0xfff) - 4;

	/* Discard oversize frames. */
	if (unlikely(pkt_len > PKT_BUF_SIZE)) {
		netif_err(lp, drv, dev, "Impossible packet size %d!\n",
			  pkt_len);
		dev->stats.rx_errors++;
		return;
	}
	if (pkt_len < 60) {
		netif_err(lp, rx_err, dev, "Runt packet!\n");
		dev->stats.rx_errors++;
		return;
	}

	if (pkt_len > rx_copybreak) {
		struct sk_buff *newskb;
		dma_addr_t new_dma_addr;

		newskb = netdev_alloc_skb(dev, PKT_BUF_SKB);
		/*
		 * map the new buffer, if mapping fails, drop the packet and
		 * reuse the old buffer
		 */
		if (newskb) {
			skb_reserve(newskb, NET_IP_ALIGN);
			new_dma_addr = pci_map_single(lp->pci_dev,
						      newskb->data,
						      PKT_BUF_SIZE,
						      PCI_DMA_FROMDEVICE);
			if (pci_dma_mapping_error(lp->pci_dev, new_dma_addr)) {
				netif_err(lp, rx_err, dev,
					  "DMA mapping error.\n");
				dev_kfree_skb(newskb);
				skb = NULL;
			} else {
				skb = lp->rx_skbuff[entry];
				pci_unmap_single(lp->pci_dev,
						 lp->rx_dma_addr[entry],
						 PKT_BUF_SIZE,
						 PCI_DMA_FROMDEVICE);
				skb_put(skb, pkt_len);
				lp->rx_skbuff[entry] = newskb;
				lp->rx_dma_addr[entry] = new_dma_addr;
				rxp->base = cpu_to_le32(new_dma_addr);
				rx_in_place = 1;
			}
		} else
			skb = NULL;
	} else
		skb = netdev_alloc_skb(dev, pkt_len + NET_IP_ALIGN);

	if (skb == NULL) {
		dev->stats.rx_dropped++;
		return;
	}
	if (!rx_in_place) {
		skb_reserve(skb, NET_IP_ALIGN);
		skb_put(skb, pkt_len);	/* Make room */
		pci_dma_sync_single_for_cpu(lp->pci_dev,
					    lp->rx_dma_addr[entry],
					    pkt_len,
					    PCI_DMA_FROMDEVICE);
		skb_copy_to_linear_data(skb,
				 (unsigned char *)(lp->rx_skbuff[entry]->data),
				 pkt_len);
		pci_dma_sync_single_for_device(lp->pci_dev,
					       lp->rx_dma_addr[entry],
					       pkt_len,
					       PCI_DMA_FROMDEVICE);
	}
	dev->stats.rx_bytes += skb->len;
	skb->protocol = eth_type_trans(skb, dev);
	netif_receive_skb(skb);
	dev->stats.rx_packets++;
}