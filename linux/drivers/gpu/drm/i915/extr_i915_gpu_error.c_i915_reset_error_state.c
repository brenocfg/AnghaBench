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
struct i915_gpu_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct i915_gpu_state* first_error; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct i915_gpu_state* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  i915_gpu_state_put (struct i915_gpu_state*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_reset_error_state(struct drm_i915_private *i915)
{
	struct i915_gpu_state *error;

	spin_lock_irq(&i915->gpu_error.lock);
	error = i915->gpu_error.first_error;
	if (error != ERR_PTR(-ENODEV)) /* if disabled, always disabled */
		i915->gpu_error.first_error = NULL;
	spin_unlock_irq(&i915->gpu_error.lock);

	if (!IS_ERR_OR_NULL(error))
		i915_gpu_state_put(error);
}