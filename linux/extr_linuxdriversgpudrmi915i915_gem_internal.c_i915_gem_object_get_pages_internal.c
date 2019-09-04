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
struct sg_table {struct scatterlist* sgl; scalar_t__ nents; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct page {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  madv; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_2__ mm; TYPE_1__ base; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MADV_DONTNEED ; 
 scalar_t__ IS_I965G (struct drm_i915_private*) ; 
 scalar_t__ IS_I965GM (struct drm_i915_private*) ; 
 int MAX_ORDER ; 
 int MAYFAIL ; 
 int PAGE_SIZE ; 
 int QUIET ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_RECLAIMABLE ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned int) ; 
 struct scatterlist* __sg_next (struct scatterlist*) ; 
 struct page* alloc_pages (int,int) ; 
 scalar_t__ fls (unsigned int) ; 
 scalar_t__ get_order (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_gtt_prepare_pages (struct drm_i915_gem_object*,struct sg_table*) ; 
 int /*<<< orphan*/  internal_free_pages (struct sg_table*) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int) ; 
 int min (scalar_t__,int) ; 
 scalar_t__ sg_alloc_table (struct sg_table*,unsigned int,int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_object_get_pages_internal(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *i915 = to_i915(obj->base.dev);
	struct sg_table *st;
	struct scatterlist *sg;
	unsigned int sg_page_sizes;
	unsigned int npages;
	int max_order;
	gfp_t gfp;

	max_order = MAX_ORDER;
#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		unsigned int max_segment;

		max_segment = swiotlb_max_segment();
		if (max_segment) {
			max_segment = max_t(unsigned int, max_segment,
					    PAGE_SIZE) >> PAGE_SHIFT;
			max_order = min(max_order, ilog2(max_segment));
		}
	}
#endif

	gfp = GFP_KERNEL | __GFP_HIGHMEM | __GFP_RECLAIMABLE;
	if (IS_I965GM(i915) || IS_I965G(i915)) {
		/* 965gm cannot relocate objects above 4GiB. */
		gfp &= ~__GFP_HIGHMEM;
		gfp |= __GFP_DMA32;
	}

create_st:
	st = kmalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		return -ENOMEM;

	npages = obj->base.size / PAGE_SIZE;
	if (sg_alloc_table(st, npages, GFP_KERNEL)) {
		kfree(st);
		return -ENOMEM;
	}

	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;

	do {
		int order = min(fls(npages) - 1, max_order);
		struct page *page;

		do {
			page = alloc_pages(gfp | (order ? QUIET : MAYFAIL),
					   order);
			if (page)
				break;
			if (!order--)
				goto err;

			/* Limit subsequent allocations as well */
			max_order = order;
		} while (1);

		sg_set_page(sg, page, PAGE_SIZE << order, 0);
		sg_page_sizes |= PAGE_SIZE << order;
		st->nents++;

		npages -= 1 << order;
		if (!npages) {
			sg_mark_end(sg);
			break;
		}

		sg = __sg_next(sg);
	} while (1);

	if (i915_gem_gtt_prepare_pages(obj, st)) {
		/* Failed to dma-map try again with single page sg segments */
		if (get_order(st->sgl->length)) {
			internal_free_pages(st);
			max_order = 0;
			goto create_st;
		}
		goto err;
	}

	/* Mark the pages as dontneed whilst they are still pinned. As soon
	 * as they are unpinned they are allowed to be reaped by the shrinker,
	 * and the caller is expected to repopulate - the contents of this
	 * object are only valid whilst active and pinned.
	 */
	obj->mm.madv = I915_MADV_DONTNEED;

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	return 0;

err:
	sg_set_page(sg, NULL, 0, 0);
	sg_mark_end(sg);
	internal_free_pages(st);

	return -ENOMEM;
}