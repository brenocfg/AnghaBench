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
struct TYPE_2__ {int /*<<< orphan*/  wakeref; } ;
struct drm_i915_private {TYPE_1__ csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOMAIN_INIT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_csr_runtime_pm_get(struct drm_i915_private *dev_priv)
{
	WARN_ON(dev_priv->csr.wakeref);
	dev_priv->csr.wakeref =
		intel_display_power_get(dev_priv, POWER_DOMAIN_INIT);
}