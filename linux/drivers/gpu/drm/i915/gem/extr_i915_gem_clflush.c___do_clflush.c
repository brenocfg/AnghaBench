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
struct TYPE_2__ {int /*<<< orphan*/  pages; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  frontbuffer; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  ORIGIN_CPU ; 
 int /*<<< orphan*/  drm_clflush_sg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __do_clflush(struct drm_i915_gem_object *obj)
{
	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	drm_clflush_sg(obj->mm.pages);
	intel_frontbuffer_flush(obj->frontbuffer, ORIGIN_CPU);
}