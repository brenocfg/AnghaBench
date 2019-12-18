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
struct TYPE_3__ {int /*<<< orphan*/  rp1_freq; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN6_RC_VIDEO_FREQ ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_TIMEOUT ; 
 int /*<<< orphan*/  GEN6_RP_IDLE_HYSTERSIS ; 
 int GEN9_FREQUENCY (int /*<<< orphan*/ ) ; 
 int GT_INTERVAL_FROM_US (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen6_set_rps ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_rps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen9_enable_rps(struct drm_i915_private *dev_priv)
{
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	/* Program defaults and thresholds for RPS */
	if (IS_GEN(dev_priv, 9))
		I915_WRITE(GEN6_RC_VIDEO_FREQ,
			GEN9_FREQUENCY(dev_priv->gt_pm.rps.rp1_freq));

	/* 1 second timeout*/
	I915_WRITE(GEN6_RP_DOWN_TIMEOUT,
		GT_INTERVAL_FROM_US(dev_priv, 1000000));

	I915_WRITE(GEN6_RP_IDLE_HYSTERSIS, 0xa);

	/* Leaning on the below call to gen6_set_rps to program/setup the
	 * Up/Down EI & threshold registers, as well as the RP_CONTROL,
	 * RP_INTERRUPT_LIMITS & RPNSWREQ registers */
	reset_rps(dev_priv, gen6_set_rps);

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
}