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
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct pasemi_mac {struct pci_dev* dma_pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_unmap_page (struct pci_dev*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int pasemi_mac_unmap_tx_skb(struct pasemi_mac *mac,
				    const int nfrags,
				    struct sk_buff *skb,
				    const dma_addr_t *dmas)
{
	int f;
	struct pci_dev *pdev = mac->dma_pdev;

	pci_unmap_single(pdev, dmas[0], skb_headlen(skb), PCI_DMA_TODEVICE);

	for (f = 0; f < nfrags; f++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		pci_unmap_page(pdev, dmas[f+1], skb_frag_size(frag), PCI_DMA_TODEVICE);
	}
	dev_kfree_skb_irq(skb);

	/* Freed descriptor slot + main SKB ptr + nfrags additional ptrs,
	 * aligned up to a power of 2
	 */
	return (nfrags + 3) & ~1;
}