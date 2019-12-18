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
struct hl_device {scalar_t__ cpu_accessible_dma_address; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ VA_CPU_ACCESSIBLE_MEM_ADDR ; 
 void* hl_fw_cpu_accessible_dma_pool_alloc (struct hl_device*,size_t,scalar_t__*) ; 

void *goya_cpu_accessible_dma_pool_alloc(struct hl_device *hdev, size_t size,
					dma_addr_t *dma_handle)
{
	void *vaddr;

	vaddr = hl_fw_cpu_accessible_dma_pool_alloc(hdev, size, dma_handle);
	*dma_handle = (*dma_handle) - hdev->cpu_accessible_dma_address +
			VA_CPU_ACCESSIBLE_MEM_ADDR;

	return vaddr;
}