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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ first_error; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;

/* Variables and functions */
 scalar_t__ ERR_PTR (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void i915_disable_error_state(struct drm_i915_private *i915, int err)
{
	spin_lock_irq(&i915->gpu_error.lock);
	if (!i915->gpu_error.first_error)
		i915->gpu_error.first_error = ERR_PTR(err);
	spin_unlock_irq(&i915->gpu_error.lock);
}