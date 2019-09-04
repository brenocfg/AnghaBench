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
struct TYPE_2__ {scalar_t__ coherent_dma_mask; scalar_t__* dma_mask; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ DMA_BIT_MASK (int) ; 
 scalar_t__ DMA_MASK_NONE ; 

void arch_setup_pdev_archdata(struct platform_device *pdev)
{
	if (pdev->dev.coherent_dma_mask == DMA_MASK_NONE &&
	    pdev->dev.dma_mask == NULL) {
		pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
		pdev->dev.dma_mask = &pdev->dev.coherent_dma_mask;
	}
}