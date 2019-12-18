#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct i915_ggtt {int /*<<< orphan*/  fence_list; TYPE_2__ vm; } ;
struct i915_fence_reg {int /*<<< orphan*/  link; TYPE_1__* i915; } ;
struct TYPE_3__ {struct i915_ggtt ggtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void i915_unreserve_fence(struct i915_fence_reg *fence)
{
	struct i915_ggtt *ggtt = &fence->i915->ggtt;

	lockdep_assert_held(&ggtt->vm.mutex);

	list_add(&fence->link, &ggtt->fence_list);
}