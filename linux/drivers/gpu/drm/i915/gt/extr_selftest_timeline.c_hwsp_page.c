#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct intel_timeline {TYPE_1__* hwsp_ggtt; } ;
struct TYPE_6__ {TYPE_2__* pages; } ;
struct drm_i915_gem_object {TYPE_3__ mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgl; } ;
struct TYPE_4__ {struct drm_i915_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  i915_gem_object_has_pinned_pages (struct drm_i915_gem_object*) ; 
 struct page* sg_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *hwsp_page(struct intel_timeline *tl)
{
	struct drm_i915_gem_object *obj = tl->hwsp_ggtt->obj;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	return sg_page(obj->mm.pages->sgl);
}