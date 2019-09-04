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
struct intel_huc {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HAS_HUC (struct drm_i915_private*) ; 
 int HUC_FW_VERIFIED ; 
 int /*<<< orphan*/  HUC_STATUS2 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 struct drm_i915_private* huc_to_i915 (struct intel_huc*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

int intel_huc_check_status(struct intel_huc *huc)
{
	struct drm_i915_private *dev_priv = huc_to_i915(huc);
	u32 status;

	if (!HAS_HUC(dev_priv))
		return -ENODEV;

	intel_runtime_pm_get(dev_priv);
	status = I915_READ(HUC_STATUS2) & HUC_FW_VERIFIED;
	intel_runtime_pm_put(dev_priv);

	return status;
}