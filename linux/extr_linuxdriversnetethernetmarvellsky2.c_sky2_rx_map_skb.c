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
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  data; } ;
struct rx_ring_info {int /*<<< orphan*/  data_addr; int /*<<< orphan*/ * frag_addr; struct sk_buff* skb; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  const skb_frag_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/  const* frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  data_size ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct rx_ring_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct rx_ring_info*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int sky2_rx_map_skb(struct pci_dev *pdev, struct rx_ring_info *re,
			    unsigned size)
{
	struct sk_buff *skb = re->skb;
	int i;

	re->data_addr = pci_map_single(pdev, skb->data, size, PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(pdev, re->data_addr))
		goto mapping_error;

	dma_unmap_len_set(re, data_size, size);

	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		re->frag_addr[i] = skb_frag_dma_map(&pdev->dev, frag, 0,
						    skb_frag_size(frag),
						    DMA_FROM_DEVICE);

		if (dma_mapping_error(&pdev->dev, re->frag_addr[i]))
			goto map_page_error;
	}
	return 0;

map_page_error:
	while (--i >= 0) {
		pci_unmap_page(pdev, re->frag_addr[i],
			       skb_frag_size(&skb_shinfo(skb)->frags[i]),
			       PCI_DMA_FROMDEVICE);
	}

	pci_unmap_single(pdev, re->data_addr, dma_unmap_len(re, data_size),
			 PCI_DMA_FROMDEVICE);

mapping_error:
	if (net_ratelimit())
		dev_warn(&pdev->dev, "%s: rx mapping error\n",
			 skb->dev->name);
	return -EIO;
}