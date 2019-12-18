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
 int PAGE_MASK ; 
 int RADEON_GART_PAGE_READ ; 
 int RADEON_GART_PAGE_SNOOP ; 
 int RADEON_GART_PAGE_WRITE ; 
 int RS400_PTE_READABLE ; 
 int RS400_PTE_UNSNOOPED ; 
 int RS400_PTE_WRITEABLE ; 
 int lower_32_bits (int) ; 
 int upper_32_bits (int) ; 

uint64_t rs400_gart_get_page_entry(uint64_t addr, uint32_t flags)
{
	uint32_t entry;

	entry = (lower_32_bits(addr) & PAGE_MASK) |
		((upper_32_bits(addr) & 0xff) << 4);
	if (flags & RADEON_GART_PAGE_READ)
		entry |= RS400_PTE_READABLE;
	if (flags & RADEON_GART_PAGE_WRITE)
		entry |= RS400_PTE_WRITEABLE;
	if (!(flags & RADEON_GART_PAGE_SNOOP))
		entry |= RS400_PTE_UNSNOOPED;
	return entry;
}