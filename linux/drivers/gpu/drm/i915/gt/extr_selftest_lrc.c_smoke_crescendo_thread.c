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
struct preempt_smoke {unsigned long count; TYPE_1__* i915; int /*<<< orphan*/  batch; } ;
struct i915_gem_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_3__ {TYPE_2__ drm; } ;

/* Variables and functions */
 unsigned long I915_PRIORITY_MAX ; 
 int /*<<< orphan*/  IGT_TIMEOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __igt_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_time ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i915_gem_context* smoke_context (struct preempt_smoke*) ; 
 int smoke_submit (struct preempt_smoke*,struct i915_gem_context*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smoke_crescendo_thread(void *arg)
{
	struct preempt_smoke *smoke = arg;
	IGT_TIMEOUT(end_time);
	unsigned long count;

	count = 0;
	do {
		struct i915_gem_context *ctx = smoke_context(smoke);
		int err;

		mutex_lock(&smoke->i915->drm.struct_mutex);
		err = smoke_submit(smoke,
				   ctx, count % I915_PRIORITY_MAX,
				   smoke->batch);
		mutex_unlock(&smoke->i915->drm.struct_mutex);
		if (err)
			return err;

		count++;
	} while (!__igt_timeout(end_time, NULL));

	smoke->count = count;
	return 0;
}