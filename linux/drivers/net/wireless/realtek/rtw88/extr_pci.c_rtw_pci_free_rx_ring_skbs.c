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
struct sk_buff {scalar_t__ cb; } ;
struct TYPE_2__ {int len; } ;
struct rtw_pci_rx_ring {struct sk_buff** buf; TYPE_1__ r; } ;
struct rtw_dev {int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RTK_PCI_RX_BUF_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_pci_free_rx_ring_skbs(struct rtw_dev *rtwdev,
				      struct rtw_pci_rx_ring *rx_ring)
{
	struct pci_dev *pdev = to_pci_dev(rtwdev->dev);
	struct sk_buff *skb;
	int buf_sz = RTK_PCI_RX_BUF_SIZE;
	dma_addr_t dma;
	int i;

	for (i = 0; i < rx_ring->r.len; i++) {
		skb = rx_ring->buf[i];
		if (!skb)
			continue;

		dma = *((dma_addr_t *)skb->cb);
		pci_unmap_single(pdev, dma, buf_sz, PCI_DMA_FROMDEVICE);
		dev_kfree_skb(skb);
		rx_ring->buf[i] = NULL;
	}
}