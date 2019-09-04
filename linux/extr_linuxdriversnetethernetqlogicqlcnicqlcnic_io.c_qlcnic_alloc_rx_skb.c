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
struct qlcnic_rx_buffer {int /*<<< orphan*/  dma; struct sk_buff* skb; } ;
struct qlcnic_host_rds_ring {int /*<<< orphan*/  dma_size; int /*<<< orphan*/  skb_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_dma_map_error; int /*<<< orphan*/  skb_alloc_failure; } ;
struct qlcnic_adapter {TYPE_1__ stats; int /*<<< orphan*/  netdev; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_alloc_rx_skb(struct qlcnic_adapter *adapter,
			       struct qlcnic_host_rds_ring *rds_ring,
			       struct qlcnic_rx_buffer *buffer)
{
	struct sk_buff *skb;
	dma_addr_t dma;
	struct pci_dev *pdev = adapter->pdev;

	skb = netdev_alloc_skb(adapter->netdev, rds_ring->skb_size);
	if (!skb) {
		adapter->stats.skb_alloc_failure++;
		return -ENOMEM;
	}

	skb_reserve(skb, NET_IP_ALIGN);
	dma = pci_map_single(pdev, skb->data,
			     rds_ring->dma_size, PCI_DMA_FROMDEVICE);

	if (pci_dma_mapping_error(pdev, dma)) {
		adapter->stats.rx_dma_map_error++;
		dev_kfree_skb_any(skb);
		return -ENOMEM;
	}

	buffer->skb = skb;
	buffer->dma = dma;

	return 0;
}