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
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sg_table* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  __i915_gem_object_set_pages (struct drm_i915_gem_object*,struct sg_table*,unsigned int) ; 
 int __sg_alloc_table_from_pages (struct sg_table*,struct page**,int,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 int i915_gem_gtt_prepare_pages (struct drm_i915_gem_object*,struct sg_table*) ; 
 unsigned int i915_sg_page_sizes (int /*<<< orphan*/ ) ; 
 unsigned int i915_sg_segment_size () ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 struct sg_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 

__attribute__((used)) static struct sg_table *
__i915_gem_userptr_alloc_pages(struct drm_i915_gem_object *obj,
			       struct page **pvec, int num_pages)
{
	unsigned int max_segment = i915_sg_segment_size();
	struct sg_table *st;
	unsigned int sg_page_sizes;
	int ret;

	st = kmalloc(sizeof(*st), GFP_KERNEL);
	if (!st)
		return ERR_PTR(-ENOMEM);

alloc_table:
	ret = __sg_alloc_table_from_pages(st, pvec, num_pages,
					  0, num_pages << PAGE_SHIFT,
					  max_segment,
					  GFP_KERNEL);
	if (ret) {
		kfree(st);
		return ERR_PTR(ret);
	}

	ret = i915_gem_gtt_prepare_pages(obj, st);
	if (ret) {
		sg_free_table(st);

		if (max_segment > PAGE_SIZE) {
			max_segment = PAGE_SIZE;
			goto alloc_table;
		}

		kfree(st);
		return ERR_PTR(ret);
	}

	sg_page_sizes = i915_sg_page_sizes(st->sgl);

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	return st;
}