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
struct hl_device {int /*<<< orphan*/  dma_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t GOYA_DMA_POOL_BLK_SIZE ; 
 scalar_t__ HOST_PHYS_BASE ; 
 void* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *goya_dma_pool_zalloc(struct hl_device *hdev, size_t size,
					gfp_t mem_flags, dma_addr_t *dma_handle)
{
	void *kernel_addr;

	if (size > GOYA_DMA_POOL_BLK_SIZE)
		return NULL;

	kernel_addr =  dma_pool_zalloc(hdev->dma_pool, mem_flags, dma_handle);

	/* Shift to the device's base physical address of host memory */
	if (kernel_addr)
		*dma_handle += HOST_PHYS_BASE;

	return kernel_addr;
}