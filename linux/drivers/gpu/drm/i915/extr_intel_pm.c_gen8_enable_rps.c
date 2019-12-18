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
struct intel_rps {int max_freq_softlimit; int min_freq_softlimit; int /*<<< orphan*/  rp1_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN6_RC_VIDEO_FREQ ; 
 int /*<<< orphan*/  GEN6_RPNSWREQ ; 
 int /*<<< orphan*/  GEN6_RP_CONTROL ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_EI ; 
 int GEN6_RP_DOWN_IDLE_AVG ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_THRESHOLD ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_TIMEOUT ; 
 int GEN6_RP_ENABLE ; 
 int /*<<< orphan*/  GEN6_RP_IDLE_HYSTERSIS ; 
 int /*<<< orphan*/  GEN6_RP_INTERRUPT_LIMITS ; 
 int GEN6_RP_MEDIA_HW_NORMAL_MODE ; 
 int GEN6_RP_MEDIA_IS_GFX ; 
 int GEN6_RP_MEDIA_TURBO ; 
 int GEN6_RP_UP_BUSY_AVG ; 
 int /*<<< orphan*/  GEN6_RP_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_UP_THRESHOLD ; 
 int HSW_FREQUENCY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen6_set_rps ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_rps (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_enable_rps(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;

	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	/* 1 Program defaults and thresholds for RPS*/
	I915_WRITE(GEN6_RPNSWREQ,
		   HSW_FREQUENCY(rps->rp1_freq));
	I915_WRITE(GEN6_RC_VIDEO_FREQ,
		   HSW_FREQUENCY(rps->rp1_freq));
	/* NB: Docs say 1s, and 1000000 - which aren't equivalent */
	I915_WRITE(GEN6_RP_DOWN_TIMEOUT, 100000000 / 128); /* 1 second timeout */

	/* Docs recommend 900MHz, and 300 MHz respectively */
	I915_WRITE(GEN6_RP_INTERRUPT_LIMITS,
		   rps->max_freq_softlimit << 24 |
		   rps->min_freq_softlimit << 16);

	I915_WRITE(GEN6_RP_UP_THRESHOLD, 7600000 / 128); /* 76ms busyness per EI, 90% */
	I915_WRITE(GEN6_RP_DOWN_THRESHOLD, 31300000 / 128); /* 313ms busyness per EI, 70%*/
	I915_WRITE(GEN6_RP_UP_EI, 66000); /* 84.48ms, XXX: random? */
	I915_WRITE(GEN6_RP_DOWN_EI, 350000); /* 448ms, XXX: random? */

	I915_WRITE(GEN6_RP_IDLE_HYSTERSIS, 10);

	/* 2: Enable RPS */
	I915_WRITE(GEN6_RP_CONTROL,
		   GEN6_RP_MEDIA_TURBO |
		   GEN6_RP_MEDIA_HW_NORMAL_MODE |
		   GEN6_RP_MEDIA_IS_GFX |
		   GEN6_RP_ENABLE |
		   GEN6_RP_UP_BUSY_AVG |
		   GEN6_RP_DOWN_IDLE_AVG);

	reset_rps(dev_priv, gen6_set_rps);

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
}