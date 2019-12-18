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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct intel_runtime_info {int* platform_mask; } ;
struct intel_device_info {int /*<<< orphan*/  platform; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (unsigned int const) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  INTEL_DEVID (struct drm_i915_private*) ; 
 struct intel_device_info* INTEL_INFO (struct drm_i915_private*) ; 
 int INTEL_SUBPLATFORM_BITS ; 
 unsigned int const INTEL_SUBPLATFORM_PORTF ; 
 unsigned int const INTEL_SUBPLATFORM_ULT ; 
 unsigned int const INTEL_SUBPLATFORM_ULX ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 struct intel_runtime_info* RUNTIME_INFO (struct drm_i915_private*) ; 
 unsigned int __platform_mask_bit (struct intel_runtime_info const*,int /*<<< orphan*/ ) ; 
 unsigned int __platform_mask_index (struct intel_runtime_info const*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_devid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subplatform_portf_ids ; 
 int /*<<< orphan*/  subplatform_ult_ids ; 
 int /*<<< orphan*/  subplatform_ulx_ids ; 

void intel_device_info_subplatform_init(struct drm_i915_private *i915)
{
	const struct intel_device_info *info = INTEL_INFO(i915);
	const struct intel_runtime_info *rinfo = RUNTIME_INFO(i915);
	const unsigned int pi = __platform_mask_index(rinfo, info->platform);
	const unsigned int pb = __platform_mask_bit(rinfo, info->platform);
	u16 devid = INTEL_DEVID(i915);
	u32 mask = 0;

	/* Make sure IS_<platform> checks are working. */
	RUNTIME_INFO(i915)->platform_mask[pi] = BIT(pb);

	/* Find and mark subplatform bits based on the PCI device id. */
	if (find_devid(devid, subplatform_ult_ids,
		       ARRAY_SIZE(subplatform_ult_ids))) {
		mask = BIT(INTEL_SUBPLATFORM_ULT);
	} else if (find_devid(devid, subplatform_ulx_ids,
			      ARRAY_SIZE(subplatform_ulx_ids))) {
		mask = BIT(INTEL_SUBPLATFORM_ULX);
		if (IS_HASWELL(i915) || IS_BROADWELL(i915)) {
			/* ULX machines are also considered ULT. */
			mask |= BIT(INTEL_SUBPLATFORM_ULT);
		}
	} else if (find_devid(devid, subplatform_portf_ids,
			      ARRAY_SIZE(subplatform_portf_ids))) {
		mask = BIT(INTEL_SUBPLATFORM_PORTF);
	}

	GEM_BUG_ON(mask & ~INTEL_SUBPLATFORM_BITS);

	RUNTIME_INFO(i915)->platform_mask[pi] |= mask;
}