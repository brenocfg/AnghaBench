#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enabled; } ;
struct TYPE_4__ {int enabled; } ;
struct TYPE_6__ {TYPE_2__ rc6; TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_3__ gt_pm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen11_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen6_reset_rps_interrupts (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_disable_gt_powersave (struct drm_i915_private*) ; 

void intel_sanitize_gt_powersave(struct drm_i915_private *dev_priv)
{
	dev_priv->gt_pm.rps.enabled = true; /* force RPS disabling */
	dev_priv->gt_pm.rc6.enabled = true; /* force RC6 disabling */
	intel_disable_gt_powersave(dev_priv);

	if (INTEL_GEN(dev_priv) >= 11)
		gen11_reset_rps_interrupts(dev_priv);
	else if (INTEL_GEN(dev_priv) >= 6)
		gen6_reset_rps_interrupts(dev_priv);
}