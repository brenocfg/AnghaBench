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
struct hl_device {TYPE_1__* pdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HOST_PHYS_BASE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,void*,scalar_t__) ; 

__attribute__((used)) static void goya_dma_free_coherent(struct hl_device *hdev, size_t size,
					void *cpu_addr, dma_addr_t dma_handle)
{
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_handle = dma_handle - HOST_PHYS_BASE;

	dma_free_coherent(&hdev->pdev->dev, size, cpu_addr, fixed_dma_handle);
}