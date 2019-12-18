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
typedef  scalar_t__ u32 ;
struct intel_rps {scalar_t__ idle_freq; scalar_t__ cur_freq; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  FORCEWAKE_MEDIA ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int valleyview_set_rps (struct drm_i915_private*,scalar_t__) ; 

__attribute__((used)) static void vlv_set_rps_idle(struct drm_i915_private *dev_priv)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	u32 val = rps->idle_freq;
	int err;

	if (rps->cur_freq <= val)
		return;

	/* The punit delays the write of the frequency and voltage until it
	 * determines the GPU is awake. During normal usage we don't want to
	 * waste power changing the frequency if the GPU is sleeping (rc6).
	 * However, the GPU and driver is now idle and we do not want to delay
	 * switching to minimum voltage (reducing power whilst idle) as we do
	 * not expect to be woken in the near future and so must flush the
	 * change by waking the device.
	 *
	 * We choose to take the media powerwell (either would do to trick the
	 * punit into committing the voltage change) as that takes a lot less
	 * power than the render powerwell.
	 */
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_MEDIA);
	err = valleyview_set_rps(dev_priv, val);
	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_MEDIA);

	if (err)
		DRM_ERROR("Failed to set RPS for idle\n");
}