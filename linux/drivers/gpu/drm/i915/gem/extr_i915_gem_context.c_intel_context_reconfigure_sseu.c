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
struct intel_sseu {int dummy; } ;
struct intel_context {TYPE_1__* engine; } ;
struct TYPE_4__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ drm; } ;
struct TYPE_3__ {struct drm_i915_private* i915; } ;

/* Variables and functions */
 int __intel_context_reconfigure_sseu (struct intel_context*,struct intel_sseu) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
intel_context_reconfigure_sseu(struct intel_context *ce, struct intel_sseu sseu)
{
	struct drm_i915_private *i915 = ce->engine->i915;
	int ret;

	ret = mutex_lock_interruptible(&i915->drm.struct_mutex);
	if (ret)
		return ret;

	ret = __intel_context_reconfigure_sseu(ce, sseu);

	mutex_unlock(&i915->drm.struct_mutex);

	return ret;
}