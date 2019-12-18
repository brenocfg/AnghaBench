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
struct sg_table {int /*<<< orphan*/  sgl; } ;
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DMA_REMAP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 struct page** dma_common_find_pages (void*) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 int sg_alloc_table (struct sg_table*,int,int /*<<< orphan*/ ) ; 
 int sg_alloc_table_from_pages (struct sg_table*,struct page**,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ ,struct page*,int,int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (void*) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static int iommu_dma_get_sgtable(struct device *dev, struct sg_table *sgt,
		void *cpu_addr, dma_addr_t dma_addr, size_t size,
		unsigned long attrs)
{
	struct page *page;
	int ret;

	if (IS_ENABLED(CONFIG_DMA_REMAP) && is_vmalloc_addr(cpu_addr)) {
		struct page **pages = dma_common_find_pages(cpu_addr);

		if (pages) {
			return sg_alloc_table_from_pages(sgt, pages,
					PAGE_ALIGN(size) >> PAGE_SHIFT,
					0, size, GFP_KERNEL);
		}

		page = vmalloc_to_page(cpu_addr);
	} else {
		page = virt_to_page(cpu_addr);
	}

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	if (!ret)
		sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	return ret;
}