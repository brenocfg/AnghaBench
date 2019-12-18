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
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slab_objects; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ global ; 
 struct drm_i915_gem_object* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct drm_i915_gem_object *i915_gem_object_alloc(void)
{
	return kmem_cache_zalloc(global.slab_objects, GFP_KERNEL);
}