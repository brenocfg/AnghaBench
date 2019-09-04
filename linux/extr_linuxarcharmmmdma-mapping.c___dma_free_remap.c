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

/* Variables and functions */
 int VM_ARM_DMA_CONSISTENT ; 
 int VM_USERMAP ; 
 int /*<<< orphan*/  dma_common_free_remap (void*,size_t,int) ; 

__attribute__((used)) static void __dma_free_remap(void *cpu_addr, size_t size)
{
	dma_common_free_remap(cpu_addr, size,
			VM_ARM_DMA_CONSISTENT | VM_USERMAP);
}