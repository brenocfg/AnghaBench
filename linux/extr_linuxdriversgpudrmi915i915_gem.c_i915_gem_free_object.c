#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  madv; scalar_t__ quirked; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  rcu; TYPE_3__ base; TYPE_1__ mm; } ;
struct drm_gem_object {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  free_count; } ;
struct TYPE_8__ {TYPE_2__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_MADV_DONTNEED ; 
 int /*<<< orphan*/  __i915_gem_free_object_rcu ; 
 int /*<<< orphan*/  __i915_gem_object_unpin_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ discard_backing_storage (struct drm_i915_gem_object*) ; 
 TYPE_4__* to_i915 (int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* to_intel_bo (struct drm_gem_object*) ; 

void i915_gem_free_object(struct drm_gem_object *gem_obj)
{
	struct drm_i915_gem_object *obj = to_intel_bo(gem_obj);

	if (obj->mm.quirked)
		__i915_gem_object_unpin_pages(obj);

	if (discard_backing_storage(obj))
		obj->mm.madv = I915_MADV_DONTNEED;

	/*
	 * Before we free the object, make sure any pure RCU-only
	 * read-side critical sections are complete, e.g.
	 * i915_gem_busy_ioctl(). For the corresponding synchronized
	 * lookup see i915_gem_object_lookup_rcu().
	 */
	atomic_inc(&to_i915(obj->base.dev)->mm.free_count);
	call_rcu(&obj->rcu, __i915_gem_free_object_rcu);
}