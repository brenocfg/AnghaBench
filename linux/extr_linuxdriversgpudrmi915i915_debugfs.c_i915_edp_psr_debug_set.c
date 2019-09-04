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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  enableddisabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_psr_irq_control (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 

__attribute__((used)) static int
i915_edp_psr_debug_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;

	if (!CAN_PSR(dev_priv))
		return -ENODEV;

	DRM_DEBUG_KMS("PSR debug %s\n", enableddisabled(val));

	intel_runtime_pm_get(dev_priv);
	intel_psr_irq_control(dev_priv, !!val);
	intel_runtime_pm_put(dev_priv);

	return 0;
}