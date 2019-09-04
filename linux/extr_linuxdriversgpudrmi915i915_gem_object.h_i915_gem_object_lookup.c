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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;
struct drm_file {int dummy; } ;

/* Variables and functions */
 struct drm_i915_gem_object* i915_gem_object_lookup_rcu (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline struct drm_i915_gem_object *
i915_gem_object_lookup(struct drm_file *file, u32 handle)
{
	struct drm_i915_gem_object *obj;

	rcu_read_lock();
	obj = i915_gem_object_lookup_rcu(file, handle);
	if (obj && !kref_get_unless_zero(&obj->base.refcount))
		obj = NULL;
	rcu_read_unlock();

	return obj;
}