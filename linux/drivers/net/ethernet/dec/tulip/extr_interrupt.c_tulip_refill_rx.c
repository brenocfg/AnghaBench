#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tulip_private {scalar_t__ cur_rx; int dirty_rx; scalar_t__ chip_id; scalar_t__ base_addr; TYPE_2__* rx_ring; TYPE_1__* rx_buffers; TYPE_3__* pdev; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {void* status; void* buffer1; } ;
struct TYPE_4__ {int /*<<< orphan*/  mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 scalar_t__ CSR2 ; 
 scalar_t__ CSR5 ; 
 int /*<<< orphan*/  DescOwned ; 
 scalar_t__ LC82C168 ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tulip_refill_rx(struct net_device *dev)
{
	struct tulip_private *tp = netdev_priv(dev);
	int entry;
	int refilled = 0;

	/* Refill the Rx ring buffers. */
	for (; tp->cur_rx - tp->dirty_rx > 0; tp->dirty_rx++) {
		entry = tp->dirty_rx % RX_RING_SIZE;
		if (tp->rx_buffers[entry].skb == NULL) {
			struct sk_buff *skb;
			dma_addr_t mapping;

			skb = tp->rx_buffers[entry].skb =
				netdev_alloc_skb(dev, PKT_BUF_SZ);
			if (skb == NULL)
				break;

			mapping = pci_map_single(tp->pdev, skb->data, PKT_BUF_SZ,
						 PCI_DMA_FROMDEVICE);
			if (dma_mapping_error(&tp->pdev->dev, mapping)) {
				dev_kfree_skb(skb);
				tp->rx_buffers[entry].skb = NULL;
				break;
			}

			tp->rx_buffers[entry].mapping = mapping;

			tp->rx_ring[entry].buffer1 = cpu_to_le32(mapping);
			refilled++;
		}
		tp->rx_ring[entry].status = cpu_to_le32(DescOwned);
	}
	if(tp->chip_id == LC82C168) {
		if(((ioread32(tp->base_addr + CSR5)>>17)&0x07) == 4) {
			/* Rx stopped due to out of buffers,
			 * restart it
			 */
			iowrite32(0x01, tp->base_addr + CSR2);
		}
	}
	return refilled;
}