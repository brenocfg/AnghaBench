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
typedef  unsigned int u64 ;
struct sg_table {scalar_t__ nents; struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_4__ {unsigned int page_mask; int /*<<< orphan*/  madv; } ;
struct TYPE_3__ {int size; } ;
struct drm_i915_gem_object {TYPE_2__ mm; TYPE_1__ base; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  I915_MADV_DONTNEED ; 
 int MAX_ORDER ; 
 int PAGE_SHIFT ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned int) ; 
 struct scatterlist* __sg_next (struct scatterlist*) ; 
 struct page* alloc_pages (int,int) ; 
 int get_order (unsigned int) ; 
 int /*<<< orphan*/  huge_pages_free_pages (struct sg_table*) ; 
 scalar_t__ i915_gem_gtt_prepare_pages (struct drm_i915_gem_object*,struct sg_table*) ; 
 unsigned int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int) ; 
 scalar_t__ sg_alloc_table (struct sg_table*,int,int) ; 
 int /*<<< orphan*/  sg_mark_end (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_huge_pages(struct drm_i915_gem_object *obj)
{
#define GFP (GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY)
	unsigned int page_mask = obj->mm.page_mask;
	struct sg_table *st;
	struct scatterlist *sg;
	unsigned int sg_page_sizes;
	u64 rem;

	st = kmalloc(sizeof(*st), GFP);
	if (!st)
		return -ENOMEM;

	if (sg_alloc_table(st, obj->base.size >> PAGE_SHIFT, GFP)) {
		kfree(st);
		return -ENOMEM;
	}

	rem = obj->base.size;
	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;

	/*
	 * Our goal here is simple, we want to greedily fill the object from
	 * largest to smallest page-size, while ensuring that we use *every*
	 * page-size as per the given page-mask.
	 */
	do {
		unsigned int bit = ilog2(page_mask);
		unsigned int page_size = BIT(bit);
		int order = get_order(page_size);

		do {
			struct page *page;

			GEM_BUG_ON(order >= MAX_ORDER);
			page = alloc_pages(GFP | __GFP_ZERO, order);
			if (!page)
				goto err;

			sg_set_page(sg, page, page_size, 0);
			sg_page_sizes |= page_size;
			st->nents++;

			rem -= page_size;
			if (!rem) {
				sg_mark_end(sg);
				break;
			}

			sg = __sg_next(sg);
		} while ((rem - ((page_size-1) & page_mask)) >= page_size);

		page_mask &= (page_size-1);
	} while (page_mask);

	if (i915_gem_gtt_prepare_pages(obj, st))
		goto err;

	obj->mm.madv = I915_MADV_DONTNEED;

	GEM_BUG_ON(sg_page_sizes != obj->mm.page_mask);
	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	return 0;

err:
	sg_set_page(sg, NULL, 0, 0);
	sg_mark_end(sg);
	huge_pages_free_pages(st);

	return -ENOMEM;
}