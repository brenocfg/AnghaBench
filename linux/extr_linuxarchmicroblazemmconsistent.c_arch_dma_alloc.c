#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {unsigned int dcache_base; unsigned int dcache_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t PAGE_ALIGN (size_t) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (struct page*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  flush_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned long) ; 
 struct page* virt_to_page (unsigned long) ; 
 scalar_t__ virt_to_phys (void*) ; 

void *arch_dma_alloc(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, unsigned long attrs)
{
	unsigned long order, vaddr;
	void *ret;
	unsigned int i, err = 0;
	struct page *page, *end;

#ifdef CONFIG_MMU
	phys_addr_t pa;
	struct vm_struct *area;
	unsigned long va;
#endif

	if (in_interrupt())
		BUG();

	/* Only allocate page size areas. */
	size = PAGE_ALIGN(size);
	order = get_order(size);

	vaddr = __get_free_pages(gfp, order);
	if (!vaddr)
		return NULL;

	/*
	 * we need to ensure that there are no cachelines in use,
	 * or worse dirty in this area.
	 */
	flush_dcache_range(virt_to_phys((void *)vaddr),
					virt_to_phys((void *)vaddr) + size);

#ifndef CONFIG_MMU
	ret = (void *)vaddr;
	/*
	 * Here's the magic!  Note if the uncached shadow is not implemented,
	 * it's up to the calling code to also test that condition and make
	 * other arranegments, such as manually flushing the cache and so on.
	 */
# ifdef CONFIG_XILINX_UNCACHED_SHADOW
	ret = (void *)((unsigned) ret | UNCACHED_SHADOW_MASK);
# endif
	if ((unsigned int)ret > cpuinfo.dcache_base &&
				(unsigned int)ret < cpuinfo.dcache_high)
		pr_warn("ERROR: Your cache coherent area is CACHED!!!\n");

	/* dma_handle is same as physical (shadowed) address */
	*dma_handle = (dma_addr_t)ret;
#else
	/* Allocate some common virtual space to map the new pages. */
	area = get_vm_area(size, VM_ALLOC);
	if (!area) {
		free_pages(vaddr, order);
		return NULL;
	}
	va = (unsigned long) area->addr;
	ret = (void *)va;

	/* This gives us the real physical address of the first page. */
	*dma_handle = pa = __virt_to_phys(vaddr);
#endif

	/*
	 * free wasted pages.  We skip the first page since we know
	 * that it will have count = 1 and won't require freeing.
	 * We also mark the pages in use as reserved so that
	 * remap_page_range works.
	 */
	page = virt_to_page(vaddr);
	end = page + (1 << order);

	split_page(page, order);

	for (i = 0; i < size && err == 0; i += PAGE_SIZE) {
#ifdef CONFIG_MMU
		/* MS: This is the whole magic - use cache inhibit pages */
		err = map_page(va + i, pa + i, _PAGE_KERNEL | _PAGE_NO_CACHE);
#endif

		SetPageReserved(page);
		page++;
	}

	/* Free the otherwise unused pages. */
	while (page < end) {
		__free_page(page);
		page++;
	}

	if (err) {
		free_pages(vaddr, order);
		return NULL;
	}

	return ret;
}