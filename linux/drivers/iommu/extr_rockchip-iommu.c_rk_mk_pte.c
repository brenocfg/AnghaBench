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
typedef  int u32 ;
typedef  int phys_addr_t ;

/* Variables and functions */
 int IOMMU_READ ; 
 int IOMMU_WRITE ; 
 int RK_PTE_PAGE_ADDRESS_MASK ; 
 int RK_PTE_PAGE_READABLE ; 
 int RK_PTE_PAGE_VALID ; 
 int RK_PTE_PAGE_WRITABLE ; 

__attribute__((used)) static u32 rk_mk_pte(phys_addr_t page, int prot)
{
	u32 flags = 0;
	flags |= (prot & IOMMU_READ) ? RK_PTE_PAGE_READABLE : 0;
	flags |= (prot & IOMMU_WRITE) ? RK_PTE_PAGE_WRITABLE : 0;
	page &= RK_PTE_PAGE_ADDRESS_MASK;
	return page | flags | RK_PTE_PAGE_VALID;
}