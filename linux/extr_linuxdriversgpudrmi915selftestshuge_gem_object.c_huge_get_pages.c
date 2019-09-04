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
struct sg_table {struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_2__ {unsigned long size; } ;
struct drm_i915_gem_object {unsigned long scratch; TYPE_1__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 int __GFP_HIGHMEM ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned long) ; 
 struct scatterlist* __sg_next (struct scatterlist*) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  huge_free_pages (struct drm_i915_gem_object*,struct sg_table*) ; 
 scalar_t__ i915_gem_gtt_prepare_pages (struct drm_i915_gem_object*,struct sg_table*) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int) ; 
 scalar_t__ sg_alloc_table (struct sg_table*,unsigned long const,int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int huge_get_pages(struct drm_i915_gem_object *obj)
{
#define GFP (GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY)
	const unsigned long nreal = obj->scratch / PAGE_SIZE;
	const unsigned long npages = obj->base.size / PAGE_SIZE;
	struct scatterlist *sg, *src, *end;
	struct sg_table *pages;
	unsigned long n;

	pages = kmalloc(sizeof(*pages), GFP);
	if (!pages)
		return -ENOMEM;

	if (sg_alloc_table(pages, npages, GFP)) {
		kfree(pages);
		return -ENOMEM;
	}

	sg = pages->sgl;
	for (n = 0; n < nreal; n++) {
		struct page *page;

		page = alloc_page(GFP | __GFP_HIGHMEM);
		if (!page) {
			sg_mark_end(sg);
			goto err;
		}

		sg_set_page(sg, page, PAGE_SIZE, 0);
		sg = __sg_next(sg);
	}
	if (nreal < npages) {
		for (end = sg, src = pages->sgl; sg; sg = __sg_next(sg)) {
			sg_set_page(sg, sg_page(src), PAGE_SIZE, 0);
			src = __sg_next(src);
			if (src == end)
				src = pages->sgl;
		}
	}

	if (i915_gem_gtt_prepare_pages(obj, pages))
		goto err;

	__i915_gem_object_set_pages(obj, pages, PAGE_SIZE);

	return 0;

err:
	huge_free_pages(obj, pages);

	return -ENOMEM;
#undef GFP
}