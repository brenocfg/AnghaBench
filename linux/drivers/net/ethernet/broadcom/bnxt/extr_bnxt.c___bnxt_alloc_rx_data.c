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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct bnxt {int rx_dma_offset; int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  rx_buf_use_size; int /*<<< orphan*/  rx_buf_size; struct pci_dev* pdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  dma_map_single_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *__bnxt_alloc_rx_data(struct bnxt *bp, dma_addr_t *mapping,
				       gfp_t gfp)
{
	u8 *data;
	struct pci_dev *pdev = bp->pdev;

	data = kmalloc(bp->rx_buf_size, gfp);
	if (!data)
		return NULL;

	*mapping = dma_map_single_attrs(&pdev->dev, data + bp->rx_dma_offset,
					bp->rx_buf_use_size, bp->rx_dir,
					DMA_ATTR_WEAK_ORDERING);

	if (dma_mapping_error(&pdev->dev, *mapping)) {
		kfree(data);
		data = NULL;
	}
	return data;
}