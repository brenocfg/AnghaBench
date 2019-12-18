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
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ HOST_PHYS_BASE ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,void*,scalar_t__) ; 

__attribute__((used)) static void goya_dma_pool_free(struct hl_device *hdev, void *vaddr,
				dma_addr_t dma_addr)
{
	/* Cancel the device's base physical address of host memory */
	dma_addr_t fixed_dma_addr = dma_addr - HOST_PHYS_BASE;

	dma_pool_free(hdev->dma_pool, vaddr, fixed_dma_addr);
}