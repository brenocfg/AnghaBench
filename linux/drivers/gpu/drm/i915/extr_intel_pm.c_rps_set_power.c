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
typedef  int u32 ;
struct TYPE_4__ {int mode; int up_threshold; int down_threshold; int /*<<< orphan*/  mutex; } ;
struct intel_rps {TYPE_2__ power; } ;
struct TYPE_3__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
#define  BETWEEN 130 
 int /*<<< orphan*/  GEN6_RP_CONTROL ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_EI ; 
 int GEN6_RP_DOWN_IDLE_AVG ; 
 int /*<<< orphan*/  GEN6_RP_DOWN_THRESHOLD ; 
 int GEN6_RP_ENABLE ; 
 int GEN6_RP_MEDIA_HW_NORMAL_MODE ; 
 int GEN6_RP_MEDIA_IS_GFX ; 
 int GEN6_RP_MEDIA_TURBO ; 
 int GEN6_RP_UP_BUSY_AVG ; 
 int /*<<< orphan*/  GEN6_RP_UP_EI ; 
 int /*<<< orphan*/  GEN6_RP_UP_THRESHOLD ; 
 int GT_INTERVAL_FROM_US (struct drm_i915_private*,int) ; 
#define  HIGH_POWER 129 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
#define  LOW_POWER 128 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rps_set_power(struct drm_i915_private *dev_priv, int new_power)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 threshold_up = 0, threshold_down = 0; /* in % */
	u32 ei_up = 0, ei_down = 0;

	lockdep_assert_held(&rps->power.mutex);

	if (new_power == rps->power.mode)
		return;

	/* Note the units here are not exactly 1us, but 1280ns. */
	switch (new_power) {
	case LOW_POWER:
		/* Upclock if more than 95% busy over 16ms */
		ei_up = 16000;
		threshold_up = 95;

		/* Downclock if less than 85% busy over 32ms */
		ei_down = 32000;
		threshold_down = 85;
		break;

	case BETWEEN:
		/* Upclock if more than 90% busy over 13ms */
		ei_up = 13000;
		threshold_up = 90;

		/* Downclock if less than 75% busy over 32ms */
		ei_down = 32000;
		threshold_down = 75;
		break;

	case HIGH_POWER:
		/* Upclock if more than 85% busy over 10ms */
		ei_up = 10000;
		threshold_up = 85;

		/* Downclock if less than 60% busy over 32ms */
		ei_down = 32000;
		threshold_down = 60;
		break;
	}

	/* When byt can survive without system hang with dynamic
	 * sw freq adjustments, this restriction can be lifted.
	 */
	if (IS_VALLEYVIEW(dev_priv))
		goto skip_hw_write;

	I915_WRITE(GEN6_RP_UP_EI,
		   GT_INTERVAL_FROM_US(dev_priv, ei_up));
	I915_WRITE(GEN6_RP_UP_THRESHOLD,
		   GT_INTERVAL_FROM_US(dev_priv,
				       ei_up * threshold_up / 100));

	I915_WRITE(GEN6_RP_DOWN_EI,
		   GT_INTERVAL_FROM_US(dev_priv, ei_down));
	I915_WRITE(GEN6_RP_DOWN_THRESHOLD,
		   GT_INTERVAL_FROM_US(dev_priv,
				       ei_down * threshold_down / 100));

	I915_WRITE(GEN6_RP_CONTROL,
		   (INTEL_GEN(dev_priv) > 9 ? 0 : GEN6_RP_MEDIA_TURBO) |
		   GEN6_RP_MEDIA_HW_NORMAL_MODE |
		   GEN6_RP_MEDIA_IS_GFX |
		   GEN6_RP_ENABLE |
		   GEN6_RP_UP_BUSY_AVG |
		   GEN6_RP_DOWN_IDLE_AVG);

skip_hw_write:
	rps->power.mode = new_power;
	rps->power.up_threshold = threshold_up;
	rps->power.down_threshold = threshold_down;
}