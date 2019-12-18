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
typedef  int u32 ;
struct TYPE_2__ {int active; scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR2_CTL ; 
 int EDP_PSR2_ENABLE ; 
 int /*<<< orphan*/  EDP_PSR_CTL ; 
 int EDP_PSR_ENABLE ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void intel_psr_exit(struct drm_i915_private *dev_priv)
{
	u32 val;

	if (!dev_priv->psr.active) {
		if (INTEL_GEN(dev_priv) >= 9)
			WARN_ON(I915_READ(EDP_PSR2_CTL) & EDP_PSR2_ENABLE);
		WARN_ON(I915_READ(EDP_PSR_CTL) & EDP_PSR_ENABLE);
		return;
	}

	if (dev_priv->psr.psr2_enabled) {
		val = I915_READ(EDP_PSR2_CTL);
		WARN_ON(!(val & EDP_PSR2_ENABLE));
		I915_WRITE(EDP_PSR2_CTL, val & ~EDP_PSR2_ENABLE);
	} else {
		val = I915_READ(EDP_PSR_CTL);
		WARN_ON(!(val & EDP_PSR_ENABLE));
		I915_WRITE(EDP_PSR_CTL, val & ~EDP_PSR_ENABLE);
	}
	dev_priv->psr.active = false;
}