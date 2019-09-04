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
struct TYPE_2__ {scalar_t__ coherent_dma; } ;
struct acpi_device {TYPE_1__ flags; } ;
typedef  enum dev_dma_attr { ____Placeholder_dev_dma_attr } dev_dma_attr ;

/* Variables and functions */
 int DEV_DMA_COHERENT ; 
 int DEV_DMA_NON_COHERENT ; 
 int DEV_DMA_NOT_SUPPORTED ; 
 int /*<<< orphan*/  acpi_dma_supported (struct acpi_device*) ; 

enum dev_dma_attr acpi_get_dma_attr(struct acpi_device *adev)
{
	if (!acpi_dma_supported(adev))
		return DEV_DMA_NOT_SUPPORTED;

	if (adev->flags.coherent_dma)
		return DEV_DMA_COHERENT;
	else
		return DEV_DMA_NON_COHERENT;
}