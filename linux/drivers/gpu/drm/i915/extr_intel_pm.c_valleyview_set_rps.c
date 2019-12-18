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
typedef  int u8 ;
struct TYPE_3__ {int cur_freq; } ;
struct TYPE_4__ {TYPE_1__ rps; } ;
struct drm_i915_private {TYPE_2__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMINTRMSK ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PUNIT_REG_GPU_FREQ_REQ ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  gen6_rps_pm_mask (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen6_set_rps_thresholds (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_gpu_freq (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  trace_intel_gpu_freq_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_punit_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  vlv_punit_put (struct drm_i915_private*) ; 
 int vlv_punit_write (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int valleyview_set_rps(struct drm_i915_private *dev_priv, u8 val)
{
	int err;

	if (WARN_ONCE(IS_CHERRYVIEW(dev_priv) && (val & 1),
		      "Odd GPU freq value\n"))
		val &= ~1;

	I915_WRITE(GEN6_PMINTRMSK, gen6_rps_pm_mask(dev_priv, val));

	if (val != dev_priv->gt_pm.rps.cur_freq) {
		vlv_punit_get(dev_priv);
		err = vlv_punit_write(dev_priv, PUNIT_REG_GPU_FREQ_REQ, val);
		vlv_punit_put(dev_priv);
		if (err)
			return err;

		gen6_set_rps_thresholds(dev_priv, val);
	}

	dev_priv->gt_pm.rps.cur_freq = val;
	trace_intel_gpu_freq_change(intel_gpu_freq(dev_priv, val));

	return 0;
}