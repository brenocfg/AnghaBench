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
struct scatterlist {int dummy; } ;
struct page {int dummy; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 struct scatterlist* i915_gem_object_get_sg (struct drm_i915_gem_object*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  i915_gem_object_has_struct_page (struct drm_i915_gem_object*) ; 
 struct page* nth_page (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

struct page *
i915_gem_object_get_page(struct drm_i915_gem_object *obj, unsigned int n)
{
	struct scatterlist *sg;
	unsigned int offset;

	GEM_BUG_ON(!i915_gem_object_has_struct_page(obj));

	sg = i915_gem_object_get_sg(obj, n, &offset);
	return nth_page(sg_page(sg), offset);
}