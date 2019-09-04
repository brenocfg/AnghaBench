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
struct live_test {scalar_t__ reset_count; int /*<<< orphan*/  name; int /*<<< orphan*/  func; struct drm_i915_private* i915; } ;
struct TYPE_2__ {scalar_t__ missed_irq_rings; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ i915_reset_count (TYPE_1__*) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_are_idle (struct drm_i915_private*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int end_live_test(struct live_test *t)
{
	struct drm_i915_private *i915 = t->i915;

	i915_retire_requests(i915);

	if (wait_for(intel_engines_are_idle(i915), 10)) {
		pr_err("%s(%s): GPU not idle\n", t->func, t->name);
		return -EIO;
	}

	if (t->reset_count != i915_reset_count(&i915->gpu_error)) {
		pr_err("%s(%s): GPU was reset %d times!\n",
		       t->func, t->name,
		       i915_reset_count(&i915->gpu_error) - t->reset_count);
		return -EIO;
	}

	if (i915->gpu_error.missed_irq_rings) {
		pr_err("%s(%s): Missed interrupts on engines %lx\n",
		       t->func, t->name, i915->gpu_error.missed_irq_rings);
		return -EIO;
	}

	return 0;
}