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
struct intel_gt {struct intel_engine_cs*** engine_class; } ;
struct intel_engine_cs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; struct intel_gt gt; } ;

/* Variables and functions */
 unsigned int MAX_ENGINE_CLASS ; 
 int MAX_ENGINE_INSTANCE ; 
 scalar_t__ USES_GUC_SUBMISSION (struct drm_i915_private*) ; 
 int mask_virtual_engine (struct drm_i915_private*,struct intel_engine_cs**,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int live_virtual_mask(void *arg)
{
	struct drm_i915_private *i915 = arg;
	struct intel_engine_cs *siblings[MAX_ENGINE_INSTANCE + 1];
	struct intel_gt *gt = &i915->gt;
	unsigned int class, inst;
	int err = 0;

	if (USES_GUC_SUBMISSION(i915))
		return 0;

	mutex_lock(&i915->drm.struct_mutex);

	for (class = 0; class <= MAX_ENGINE_CLASS; class++) {
		unsigned int nsibling;

		nsibling = 0;
		for (inst = 0; inst <= MAX_ENGINE_INSTANCE; inst++) {
			if (!gt->engine_class[class][inst])
				break;

			siblings[nsibling++] = gt->engine_class[class][inst];
		}
		if (nsibling < 2)
			continue;

		err = mask_virtual_engine(i915, siblings, nsibling);
		if (err)
			goto out_unlock;
	}

out_unlock:
	mutex_unlock(&i915->drm.struct_mutex);
	return err;
}