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
struct drm_i915_fence_reg {TYPE_3__* i915; int /*<<< orphan*/  link; } ;
struct TYPE_5__ {int /*<<< orphan*/  fence_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_6__ {TYPE_2__ mm; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void i915_unreserve_fence(struct drm_i915_fence_reg *fence)
{
	lockdep_assert_held(&fence->i915->drm.struct_mutex);

	list_add(&fence->link, &fence->i915->mm.fence_list);
}