#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skb_shared_info {size_t nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ skb_headlen (struct sk_buff const*) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static int map_skb(struct pci_dev *pdev, const struct sk_buff *skb,
		   dma_addr_t *addr)
{
	const skb_frag_t *fp, *end;
	const struct skb_shared_info *si;

	if (skb_headlen(skb)) {
		*addr = pci_map_single(pdev, skb->data, skb_headlen(skb),
				       PCI_DMA_TODEVICE);
		if (pci_dma_mapping_error(pdev, *addr))
			goto out_err;
		addr++;
	}

	si = skb_shinfo(skb);
	end = &si->frags[si->nr_frags];

	for (fp = si->frags; fp < end; fp++) {
		*addr = skb_frag_dma_map(&pdev->dev, fp, 0, skb_frag_size(fp),
					 DMA_TO_DEVICE);
		if (pci_dma_mapping_error(pdev, *addr))
			goto unwind;
		addr++;
	}
	return 0;

unwind:
	while (fp-- > si->frags)
		dma_unmap_page(&pdev->dev, *--addr, skb_frag_size(fp),
			       DMA_TO_DEVICE);

	pci_unmap_single(pdev, addr[-1], skb_headlen(skb), PCI_DMA_TODEVICE);
out_err:
	return -ENOMEM;
}