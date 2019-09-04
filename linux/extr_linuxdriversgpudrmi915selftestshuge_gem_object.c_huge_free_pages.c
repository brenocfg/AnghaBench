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
struct sg_table {struct scatterlist* sgl; } ;
struct scatterlist {int dummy; } ;
struct drm_i915_gem_object {unsigned long scratch; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 struct scatterlist* __sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  kfree (struct sg_table*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void huge_free_pages(struct drm_i915_gem_object *obj,
			    struct sg_table *pages)
{
	unsigned long nreal = obj->scratch / PAGE_SIZE;
	struct scatterlist *sg;

	for (sg = pages->sgl; sg && nreal--; sg = __sg_next(sg))
		__free_page(sg_page(sg));

	sg_free_table(pages);
	kfree(pages);
}