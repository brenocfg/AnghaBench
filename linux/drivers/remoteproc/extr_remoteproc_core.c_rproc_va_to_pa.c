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
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 scalar_t__ offset_in_page (void*) ; 
 scalar_t__ page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_addr_valid (void*) ; 
 scalar_t__ virt_to_phys (void*) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

phys_addr_t rproc_va_to_pa(void *cpu_addr)
{
	/*
	 * Return physical address according to virtual address location
	 * - in vmalloc: if region ioremapped or defined as dma_alloc_coherent
	 * - in kernel: if region allocated in generic dma memory pool
	 */
	if (is_vmalloc_addr(cpu_addr)) {
		return page_to_phys(vmalloc_to_page(cpu_addr)) +
				    offset_in_page(cpu_addr);
	}

	WARN_ON(!virt_addr_valid(cpu_addr));
	return virt_to_phys(cpu_addr);
}