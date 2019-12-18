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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_sge {int /*<<< orphan*/  len; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_set_sge (struct hinic_sge*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_sge_to_dma (struct hinic_sge*) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int tx_map_skb(struct hinic_dev *nic_dev, struct sk_buff *skb,
		      struct hinic_sge *sges)
{
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;
	struct pci_dev *pdev = hwif->pdev;
	skb_frag_t *frag;
	dma_addr_t dma_addr;
	int i, j;

	dma_addr = dma_map_single(&pdev->dev, skb->data, skb_headlen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_error(&pdev->dev, dma_addr)) {
		dev_err(&pdev->dev, "Failed to map Tx skb data\n");
		return -EFAULT;
	}

	hinic_set_sge(&sges[0], dma_addr, skb_headlen(skb));

	for (i = 0 ; i < skb_shinfo(skb)->nr_frags; i++) {
		frag = &skb_shinfo(skb)->frags[i];

		dma_addr = skb_frag_dma_map(&pdev->dev, frag, 0,
					    skb_frag_size(frag),
					    DMA_TO_DEVICE);
		if (dma_mapping_error(&pdev->dev, dma_addr)) {
			dev_err(&pdev->dev, "Failed to map Tx skb frag\n");
			goto err_tx_map;
		}

		hinic_set_sge(&sges[i + 1], dma_addr, skb_frag_size(frag));
	}

	return 0;

err_tx_map:
	for (j = 0; j < i; j++)
		dma_unmap_page(&pdev->dev, hinic_sge_to_dma(&sges[j + 1]),
			       sges[j + 1].len, DMA_TO_DEVICE);

	dma_unmap_single(&pdev->dev, hinic_sge_to_dma(&sges[0]), sges[0].len,
			 DMA_TO_DEVICE);
	return -EFAULT;
}