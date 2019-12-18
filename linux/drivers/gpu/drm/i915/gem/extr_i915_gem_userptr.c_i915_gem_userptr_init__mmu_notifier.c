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
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENODEV ; 
 int EPERM ; 
 unsigned int I915_USERPTR_UNSYNCHRONIZED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_gem_userptr_init__mmu_notifier(struct drm_i915_gem_object *obj,
				    unsigned flags)
{
	if ((flags & I915_USERPTR_UNSYNCHRONIZED) == 0)
		return -ENODEV;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	return 0;
}