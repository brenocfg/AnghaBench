#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct i915_address_space {unsigned int scratch_order; int /*<<< orphan*/  dma; TYPE_2__* scratch; int /*<<< orphan*/  i915; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; struct page* page; } ;
struct TYPE_4__ {TYPE_1__ base; } ;

/* Variables and functions */
 int DMA_ATTR_NO_WARN ; 
 int DMA_ATTR_SKIP_CPU_SYNC ; 
 int ENOMEM ; 
 scalar_t__ HAS_PAGE_SIZES (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long I915_GTT_PAGE_SIZE_4K ; 
 unsigned long I915_GTT_PAGE_SIZE_64K ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int __GFP_NOWARN ; 
 int __GFP_RETRY_MAYFAIL ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 struct page* alloc_pages (int,unsigned int) ; 
 int /*<<< orphan*/  dma_map_page_attrs (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned int get_order (unsigned long) ; 
 scalar_t__ i915_vm_is_4lvl (struct i915_address_space*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
setup_scratch_page(struct i915_address_space *vm, gfp_t gfp)
{
	unsigned long size;

	/*
	 * In order to utilize 64K pages for an object with a size < 2M, we will
	 * need to support a 64K scratch page, given that every 16th entry for a
	 * page-table operating in 64K mode must point to a properly aligned 64K
	 * region, including any PTEs which happen to point to scratch.
	 *
	 * This is only relevant for the 48b PPGTT where we support
	 * huge-gtt-pages, see also i915_vma_insert(). However, as we share the
	 * scratch (read-only) between all vm, we create one 64k scratch page
	 * for all.
	 */
	size = I915_GTT_PAGE_SIZE_4K;
	if (i915_vm_is_4lvl(vm) &&
	    HAS_PAGE_SIZES(vm->i915, I915_GTT_PAGE_SIZE_64K)) {
		size = I915_GTT_PAGE_SIZE_64K;
		gfp |= __GFP_NOWARN;
	}
	gfp |= __GFP_ZERO | __GFP_RETRY_MAYFAIL;

	do {
		unsigned int order = get_order(size);
		struct page *page;
		dma_addr_t addr;

		page = alloc_pages(gfp, order);
		if (unlikely(!page))
			goto skip;

		addr = dma_map_page_attrs(vm->dma,
					  page, 0, size,
					  PCI_DMA_BIDIRECTIONAL,
					  DMA_ATTR_SKIP_CPU_SYNC |
					  DMA_ATTR_NO_WARN);
		if (unlikely(dma_mapping_error(vm->dma, addr)))
			goto free_page;

		if (unlikely(!IS_ALIGNED(addr, size)))
			goto unmap_page;

		vm->scratch[0].base.page = page;
		vm->scratch[0].base.daddr = addr;
		vm->scratch_order = order;
		return 0;

unmap_page:
		dma_unmap_page(vm->dma, addr, size, PCI_DMA_BIDIRECTIONAL);
free_page:
		__free_pages(page, order);
skip:
		if (size == I915_GTT_PAGE_SIZE_4K)
			return -ENOMEM;

		size = I915_GTT_PAGE_SIZE_4K;
		gfp &= ~__GFP_NOWARN;
	} while (1);
}