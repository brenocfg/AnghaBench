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
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 unsigned long DW_PER_PAGE ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 unsigned long fake_page_count (struct drm_i915_gem_object*) ; 

__attribute__((used)) static unsigned long max_dwords(struct drm_i915_gem_object *obj)
{
	unsigned long npages = fake_page_count(obj);

	GEM_BUG_ON(!IS_ALIGNED(npages, DW_PER_PAGE));
	return npages / DW_PER_PAGE;
}