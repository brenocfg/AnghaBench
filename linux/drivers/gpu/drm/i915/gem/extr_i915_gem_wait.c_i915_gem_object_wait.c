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
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct drm_i915_gem_object {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 long i915_gem_object_wait_reservation (int /*<<< orphan*/ ,unsigned int,long) ; 
 int /*<<< orphan*/  might_sleep () ; 

int
i915_gem_object_wait(struct drm_i915_gem_object *obj,
		     unsigned int flags,
		     long timeout)
{
	might_sleep();
	GEM_BUG_ON(timeout < 0);

	timeout = i915_gem_object_wait_reservation(obj->base.resv,
						   flags, timeout);
	return timeout < 0 ? timeout : 0;
}