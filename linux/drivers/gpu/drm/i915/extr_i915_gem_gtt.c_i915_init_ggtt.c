#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_private {int /*<<< orphan*/  ggtt; } ;

/* Variables and functions */
 scalar_t__ INTEL_PPGTT (struct drm_i915_private*) ; 
 scalar_t__ INTEL_PPGTT_ALIASING ; 
 int /*<<< orphan*/  cleanup_init_ggtt (int /*<<< orphan*/ *) ; 
 int init_aliasing_ppgtt (int /*<<< orphan*/ *) ; 
 int init_ggtt (int /*<<< orphan*/ *) ; 

int i915_init_ggtt(struct drm_i915_private *i915)
{
	int ret;

	ret = init_ggtt(&i915->ggtt);
	if (ret)
		return ret;

	if (INTEL_PPGTT(i915) == INTEL_PPGTT_ALIASING) {
		ret = init_aliasing_ppgtt(&i915->ggtt);
		if (ret)
			cleanup_init_ggtt(&i915->ggtt);
	}

	return 0;
}