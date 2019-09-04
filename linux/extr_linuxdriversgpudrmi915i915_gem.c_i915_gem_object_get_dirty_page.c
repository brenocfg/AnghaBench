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
struct TYPE_2__ {int /*<<< orphan*/  dirty; } ;
struct drm_i915_gem_object {TYPE_1__ mm; } ;

/* Variables and functions */
 struct page* i915_gem_object_get_page (struct drm_i915_gem_object*,unsigned int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

struct page *
i915_gem_object_get_dirty_page(struct drm_i915_gem_object *obj,
			       unsigned int n)
{
	struct page *page;

	page = i915_gem_object_get_page(obj, n);
	if (!obj->mm.dirty)
		set_page_dirty(page);

	return page;
}