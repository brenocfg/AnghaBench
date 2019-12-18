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
typedef  int u64 ;
typedef  int u32 ;
struct intel_rps_ei {int render_c0; int media_c0; scalar_t__ ktime; } ;
struct TYPE_4__ {int up_threshold; int down_threshold; } ;
struct intel_rps {struct intel_rps_ei ei; TYPE_2__ power; } ;
struct TYPE_3__ {struct intel_rps rps; } ;
struct drm_i915_private {int czclk_freq; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int GEN6_PM_RP_DOWN_THRESHOLD ; 
 int GEN6_PM_RP_UP_EI_EXPIRED ; 
 int GEN6_PM_RP_UP_THRESHOLD ; 
 int ktime_us_delta (scalar_t__,scalar_t__) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  vlv_c0_read (struct drm_i915_private*,struct intel_rps_ei*) ; 

__attribute__((used)) static u32 vlv_wa_c0_ei(struct drm_i915_private *dev_priv, u32 pm_iir)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	const struct intel_rps_ei *prev = &rps->ei;
	struct intel_rps_ei now;
	u32 events = 0;

	if ((pm_iir & GEN6_PM_RP_UP_EI_EXPIRED) == 0)
		return 0;

	vlv_c0_read(dev_priv, &now);

	if (prev->ktime) {
		u64 time, c0;
		u32 render, media;

		time = ktime_us_delta(now.ktime, prev->ktime);

		time *= dev_priv->czclk_freq;

		/* Workload can be split between render + media,
		 * e.g. SwapBuffers being blitted in X after being rendered in
		 * mesa. To account for this we need to combine both engines
		 * into our activity counter.
		 */
		render = now.render_c0 - prev->render_c0;
		media = now.media_c0 - prev->media_c0;
		c0 = max(render, media);
		c0 *= 1000 * 100 << 8; /* to usecs and scale to threshold% */

		if (c0 > time * rps->power.up_threshold)
			events = GEN6_PM_RP_UP_THRESHOLD;
		else if (c0 < time * rps->power.down_threshold)
			events = GEN6_PM_RP_DOWN_THRESHOLD;
	}

	rps->ei = now;
	return events;
}