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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int dummy; } ;
struct nx_host_rds_ring {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  skb_size; } ;
struct netxen_rx_buffer {int /*<<< orphan*/  state; int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  cut_through; } ;
struct netxen_adapter {TYPE_1__ ahw; int /*<<< orphan*/  netdev; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_BUFFER_BUSY ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int
netxen_alloc_rx_skb(struct netxen_adapter *adapter,
		struct nx_host_rds_ring *rds_ring,
		struct netxen_rx_buffer *buffer)
{
	struct sk_buff *skb;
	dma_addr_t dma;
	struct pci_dev *pdev = adapter->pdev;

	buffer->skb = netdev_alloc_skb(adapter->netdev, rds_ring->skb_size);
	if (!buffer->skb)
		return 1;

	skb = buffer->skb;

	if (!adapter->ahw.cut_through)
		skb_reserve(skb, 2);

	dma = pci_map_single(pdev, skb->data,
			rds_ring->dma_size, PCI_DMA_FROMDEVICE);

	if (pci_dma_mapping_error(pdev, dma)) {
		dev_kfree_skb_any(skb);
		buffer->skb = NULL;
		return 1;
	}

	buffer->skb = skb;
	buffer->dma = dma;
	buffer->state = NETXEN_BUFFER_BUSY;

	return 0;
}