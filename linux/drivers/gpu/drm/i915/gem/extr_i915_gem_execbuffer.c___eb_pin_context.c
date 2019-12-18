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
struct intel_context {int /*<<< orphan*/  pin_count; } ;
struct i915_execbuffer {TYPE_2__* i915; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int __intel_context_do_pin (struct intel_context*) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__eb_pin_context(struct i915_execbuffer *eb, struct intel_context *ce)
{
	int err;

	if (likely(atomic_inc_not_zero(&ce->pin_count)))
		return 0;

	err = mutex_lock_interruptible(&eb->i915->drm.struct_mutex);
	if (err)
		return err;

	err = __intel_context_do_pin(ce);
	mutex_unlock(&eb->i915->drm.struct_mutex);

	return err;
}