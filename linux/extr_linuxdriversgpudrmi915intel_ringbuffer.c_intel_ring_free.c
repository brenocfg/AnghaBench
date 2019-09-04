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
struct intel_ring {int /*<<< orphan*/  timeline; TYPE_1__* vma; } ;
struct drm_i915_gem_object {int dummy; } ;
struct TYPE_2__ {struct drm_i915_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_object_release_unless_active (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_timeline_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_vma_close (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct intel_ring*) ; 

void
intel_ring_free(struct intel_ring *ring)
{
	struct drm_i915_gem_object *obj = ring->vma->obj;

	i915_vma_close(ring->vma);
	__i915_gem_object_release_unless_active(obj);

	i915_timeline_put(ring->timeline);
	kfree(ring);
}