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
struct sg_table {int dummy; } ;
struct TYPE_2__ {scalar_t__ madv; int dirty; } ;
struct drm_i915_gem_object {int read_domains; int cache_coherent; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_BO_CACHE_COHERENT_FOR_READ ; 
 int I915_GEM_DOMAIN_CPU ; 
 scalar_t__ I915_MADV_DONTNEED ; 
 scalar_t__ __I915_MADV_PURGED ; 
 int /*<<< orphan*/  __start_cpu_write (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  drm_clflush_sg (struct sg_table*) ; 

void
__i915_gem_object_release_shmem(struct drm_i915_gem_object *obj,
				struct sg_table *pages,
				bool needs_clflush)
{
	GEM_BUG_ON(obj->mm.madv == __I915_MADV_PURGED);

	if (obj->mm.madv == I915_MADV_DONTNEED)
		obj->mm.dirty = false;

	if (needs_clflush &&
	    (obj->read_domains & I915_GEM_DOMAIN_CPU) == 0 &&
	    !(obj->cache_coherent & I915_BO_CACHE_COHERENT_FOR_READ))
		drm_clflush_sg(pages);

	__start_cpu_write(obj);
}