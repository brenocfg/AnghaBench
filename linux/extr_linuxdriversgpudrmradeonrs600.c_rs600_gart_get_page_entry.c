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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int R600_PTE_READABLE ; 
 int R600_PTE_SNOOPED ; 
 int R600_PTE_SYSTEM ; 
 int R600_PTE_VALID ; 
 int R600_PTE_WRITEABLE ; 
 int RADEON_GART_PAGE_READ ; 
 int RADEON_GART_PAGE_SNOOP ; 
 int RADEON_GART_PAGE_VALID ; 
 int RADEON_GART_PAGE_WRITE ; 

uint64_t rs600_gart_get_page_entry(uint64_t addr, uint32_t flags)
{
	addr = addr & 0xFFFFFFFFFFFFF000ULL;
	addr |= R600_PTE_SYSTEM;
	if (flags & RADEON_GART_PAGE_VALID)
		addr |= R600_PTE_VALID;
	if (flags & RADEON_GART_PAGE_READ)
		addr |= R600_PTE_READABLE;
	if (flags & RADEON_GART_PAGE_WRITE)
		addr |= R600_PTE_WRITEABLE;
	if (flags & RADEON_GART_PAGE_SNOOP)
		addr |= R600_PTE_SNOOPED;
	return addr;
}