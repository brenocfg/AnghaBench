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
typedef  size_t uint64_t ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 

__attribute__((used)) static uint64_t amdgpu_vm_map_gart(const dma_addr_t *pages_addr, uint64_t addr)
{
	uint64_t result;

	/* page table offset */
	result = pages_addr[addr >> PAGE_SHIFT];

	/* in case cpu page size != gpu page size*/
	result |= addr & (~PAGE_MASK);

	result &= 0xFFFFFFFFFFFFF000ULL;

	return result;
}