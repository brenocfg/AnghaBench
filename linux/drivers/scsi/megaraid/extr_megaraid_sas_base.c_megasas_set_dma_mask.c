#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_8__ {scalar_t__* dma_mask; scalar_t__ coherent_dma_mask; } ;
struct pci_dev {TYPE_2__ dev; } ;
struct megasas_instance {scalar_t__ adapter_type; int consistent_mask_64bit; TYPE_1__* reg_set; struct pci_dev* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  outbound_scratch_pad_1; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 scalar_t__ IS_DMA64 ; 
 int MR_CAN_HANDLE_64_BIT_DMA_OFFSET ; 
 scalar_t__ VENTURA_SERIES ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,char*,char*) ; 
 scalar_t__ dma_set_coherent_mask (TYPE_2__*,scalar_t__) ; 
 scalar_t__ dma_set_mask (TYPE_2__*,scalar_t__) ; 
 scalar_t__ dma_set_mask_and_coherent (TYPE_2__*,scalar_t__) ; 
 int megasas_readl (struct megasas_instance*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
megasas_set_dma_mask(struct megasas_instance *instance)
{
	u64 consistent_mask;
	struct pci_dev *pdev;
	u32 scratch_pad_1;

	pdev = instance->pdev;
	consistent_mask = (instance->adapter_type >= VENTURA_SERIES) ?
				DMA_BIT_MASK(63) : DMA_BIT_MASK(32);

	if (IS_DMA64) {
		if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(63)) &&
		    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))
			goto fail_set_dma_mask;

		if ((*pdev->dev.dma_mask == DMA_BIT_MASK(63)) &&
		    (dma_set_coherent_mask(&pdev->dev, consistent_mask) &&
		     dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))) {
			/*
			 * If 32 bit DMA mask fails, then try for 64 bit mask
			 * for FW capable of handling 64 bit DMA.
			 */
			scratch_pad_1 = megasas_readl
				(instance, &instance->reg_set->outbound_scratch_pad_1);

			if (!(scratch_pad_1 & MR_CAN_HANDLE_64_BIT_DMA_OFFSET))
				goto fail_set_dma_mask;
			else if (dma_set_mask_and_coherent(&pdev->dev,
							   DMA_BIT_MASK(63)))
				goto fail_set_dma_mask;
		}
	} else if (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32)))
		goto fail_set_dma_mask;

	if (pdev->dev.coherent_dma_mask == DMA_BIT_MASK(32))
		instance->consistent_mask_64bit = false;
	else
		instance->consistent_mask_64bit = true;

	dev_info(&pdev->dev, "%s bit DMA mask and %s bit consistent mask\n",
		 ((*pdev->dev.dma_mask == DMA_BIT_MASK(63)) ? "63" : "32"),
		 (instance->consistent_mask_64bit ? "63" : "32"));

	return 0;

fail_set_dma_mask:
	dev_err(&pdev->dev, "Failed to set DMA mask\n");
	return -1;

}