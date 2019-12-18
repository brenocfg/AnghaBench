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
struct intel_device_info {unsigned int engine_mask; } ;
struct drm_i915_private {int /*<<< orphan*/  gt; } ;
struct TYPE_4__ {unsigned int engine_mask; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_engines; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int BIT (unsigned int) ; 
 scalar_t__ BITS_PER_TYPE (unsigned int) ; 
 int ENODEV ; 
 unsigned int const GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_ENGINE (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  I915_NUM_ENGINES ; 
 TYPE_2__* INTEL_INFO (struct drm_i915_private*) ; 
 TYPE_1__* RUNTIME_INFO (struct drm_i915_private*) ; 
 scalar_t__ WARN_ON (unsigned int const) ; 
 int /*<<< orphan*/  hweight32 (unsigned int) ; 
 scalar_t__ i915_inject_probe_failure (struct drm_i915_private*) ; 
 int intel_engine_setup (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  intel_engines ; 
 int /*<<< orphan*/  intel_engines_cleanup (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_gt_check_and_clear_faults (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_setup_engine_capabilities (struct drm_i915_private*) ; 
 struct intel_device_info* mkwrite_device_info (struct drm_i915_private*) ; 

int intel_engines_init_mmio(struct drm_i915_private *i915)
{
	struct intel_device_info *device_info = mkwrite_device_info(i915);
	const unsigned int engine_mask = INTEL_INFO(i915)->engine_mask;
	unsigned int mask = 0;
	unsigned int i;
	int err;

	WARN_ON(engine_mask == 0);
	WARN_ON(engine_mask &
		GENMASK(BITS_PER_TYPE(mask) - 1, I915_NUM_ENGINES));

	if (i915_inject_probe_failure(i915))
		return -ENODEV;

	for (i = 0; i < ARRAY_SIZE(intel_engines); i++) {
		if (!HAS_ENGINE(i915, i))
			continue;

		err = intel_engine_setup(&i915->gt, i);
		if (err)
			goto cleanup;

		mask |= BIT(i);
	}

	/*
	 * Catch failures to update intel_engines table when the new engines
	 * are added to the driver by a warning and disabling the forgotten
	 * engines.
	 */
	if (WARN_ON(mask != engine_mask))
		device_info->engine_mask = mask;

	RUNTIME_INFO(i915)->num_engines = hweight32(mask);

	intel_gt_check_and_clear_faults(&i915->gt);

	intel_setup_engine_capabilities(i915);

	return 0;

cleanup:
	intel_engines_cleanup(i915);
	return err;
}