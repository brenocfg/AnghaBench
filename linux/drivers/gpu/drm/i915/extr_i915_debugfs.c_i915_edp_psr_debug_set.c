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
typedef  int /*<<< orphan*/  u64 ;
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int intel_psr_debug_set (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_edp_psr_debug_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;
	intel_wakeref_t wakeref;
	int ret;

	if (!CAN_PSR(dev_priv))
		return -ENODEV;

	DRM_DEBUG_KMS("Setting PSR debug to %llx\n", val);

	wakeref = intel_runtime_pm_get(&dev_priv->runtime_pm);

	ret = intel_psr_debug_set(dev_priv, val);

	intel_runtime_pm_put(&dev_priv->runtime_pm, wakeref);

	return ret;
}