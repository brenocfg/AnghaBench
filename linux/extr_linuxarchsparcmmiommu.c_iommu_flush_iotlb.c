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
typedef  int /*<<< orphan*/  iopte_t ;

/* Variables and functions */
 unsigned long PAGE_ALIGN (unsigned long) ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_page_to_ram (unsigned long) ; 
 scalar_t__ viking_flush ; 
 int /*<<< orphan*/  viking_flush_page (unsigned long) ; 
 int /*<<< orphan*/  viking_mxcc_flush_page (unsigned long) ; 
 scalar_t__ viking_mxcc_present ; 

__attribute__((used)) static void iommu_flush_iotlb(iopte_t *iopte, unsigned int niopte)
{
	unsigned long start;
	unsigned long end;

	start = (unsigned long)iopte;
	end = PAGE_ALIGN(start + niopte*sizeof(iopte_t));
	start &= PAGE_MASK;
	if (viking_mxcc_present) {
		while(start < end) {
			viking_mxcc_flush_page(start);
			start += PAGE_SIZE;
		}
	} else if (viking_flush) {
		while(start < end) {
			viking_flush_page(start);
			start += PAGE_SIZE;
		}
	} else {
		while(start < end) {
			__flush_page_to_ram(start);
			start += PAGE_SIZE;
		}
	}
}