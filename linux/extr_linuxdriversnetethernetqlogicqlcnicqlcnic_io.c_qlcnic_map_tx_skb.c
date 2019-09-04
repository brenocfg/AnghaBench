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
struct skb_frag_struct {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct qlcnic_skb_frag {void* dma; int /*<<< orphan*/  length; } ;
struct qlcnic_cmd_buffer {struct qlcnic_skb_frag* frag_array; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  void* dma_addr_t ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,void*) ; 
 void* pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ *,struct skb_frag_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (struct skb_frag_struct*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int qlcnic_map_tx_skb(struct pci_dev *pdev, struct sk_buff *skb,
			     struct qlcnic_cmd_buffer *pbuf)
{
	struct qlcnic_skb_frag *nf;
	struct skb_frag_struct *frag;
	int i, nr_frags;
	dma_addr_t map;

	nr_frags = skb_shinfo(skb)->nr_frags;
	nf = &pbuf->frag_array[0];

	map = pci_map_single(pdev, skb->data, skb_headlen(skb),
			     PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(pdev, map))
		goto out_err;

	nf->dma = map;
	nf->length = skb_headlen(skb);

	for (i = 0; i < nr_frags; i++) {
		frag = &skb_shinfo(skb)->frags[i];
		nf = &pbuf->frag_array[i+1];
		map = skb_frag_dma_map(&pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, map))
			goto unwind;

		nf->dma = map;
		nf->length = skb_frag_size(frag);
	}

	return 0;

unwind:
	while (--i >= 0) {
		nf = &pbuf->frag_array[i+1];
		pci_unmap_page(pdev, nf->dma, nf->length, PCI_DMA_TODEVICE);
	}

	nf = &pbuf->frag_array[0];
	pci_unmap_single(pdev, nf->dma, skb_headlen(skb), PCI_DMA_TODEVICE);

out_err:
	return -ENOMEM;
}