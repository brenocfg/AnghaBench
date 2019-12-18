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
struct mtd_info {void* priv; } ;
typedef  unsigned long resource_size_t ;
typedef  int loff_t ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int __pfn_to_phys (unsigned long) ; 
 int /*<<< orphan*/  offset_in_page (void*) ; 
 unsigned long vmalloc_to_pfn (void*) ; 

__attribute__((used)) static int ram_point(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, void **virt, resource_size_t *phys)
{
	*virt = mtd->priv + from;
	*retlen = len;

	if (phys) {
		/* limit retlen to the number of contiguous physical pages */
		unsigned long page_ofs = offset_in_page(*virt);
		void *addr = *virt - page_ofs;
		unsigned long pfn1, pfn0 = vmalloc_to_pfn(addr);

		*phys = __pfn_to_phys(pfn0) + page_ofs;
		len += page_ofs;
		while (len > PAGE_SIZE) {
			len -= PAGE_SIZE;
			addr += PAGE_SIZE;
			pfn0++;
			pfn1 = vmalloc_to_pfn(addr);
			if (pfn1 != pfn0) {
				*retlen = addr - *virt;
				break;
			}
		}
	}

	return 0;
}