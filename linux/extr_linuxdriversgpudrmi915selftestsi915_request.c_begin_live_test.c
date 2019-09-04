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
struct live_test {char const* func; char const* name; int /*<<< orphan*/  reset_count; struct drm_i915_private* i915; } ;
struct TYPE_2__ {scalar_t__ missed_irq_rings; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_reset_count (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,char const*,int) ; 

__attribute__((used)) static int begin_live_test(struct live_test *t,
			   struct drm_i915_private *i915,
			   const char *func,
			   const char *name)
{
	int err;

	t->i915 = i915;
	t->func = func;
	t->name = name;

	err = i915_gem_wait_for_idle(i915,
				     I915_WAIT_LOCKED,
				     MAX_SCHEDULE_TIMEOUT);
	if (err) {
		pr_err("%s(%s): failed to idle before, with err=%d!",
		       func, name, err);
		return err;
	}

	i915->gpu_error.missed_irq_rings = 0;
	t->reset_count = i915_reset_count(&i915->gpu_error);

	return 0;
}