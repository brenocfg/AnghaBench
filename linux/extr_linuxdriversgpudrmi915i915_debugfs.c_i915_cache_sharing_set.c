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
typedef  int u64 ;
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GEN6_MBCUNIT_SNPCR ; 
 int GEN6_MBC_SNPCR_MASK ; 
 int GEN6_MBC_SNPCR_SHIFT ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN6 (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN7 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

__attribute__((used)) static int
i915_cache_sharing_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;
	u32 snpcr;

	if (!(IS_GEN6(dev_priv) || IS_GEN7(dev_priv)))
		return -ENODEV;

	if (val > 3)
		return -EINVAL;

	intel_runtime_pm_get(dev_priv);
	DRM_DEBUG_DRIVER("Manually setting uncore sharing to %llu\n", val);

	/* Update the cache sharing policy here as well */
	snpcr = I915_READ(GEN6_MBCUNIT_SNPCR);
	snpcr &= ~GEN6_MBC_SNPCR_MASK;
	snpcr |= (val << GEN6_MBC_SNPCR_SHIFT);
	I915_WRITE(GEN6_MBCUNIT_SNPCR, snpcr);

	intel_runtime_pm_put(dev_priv);
	return 0;
}