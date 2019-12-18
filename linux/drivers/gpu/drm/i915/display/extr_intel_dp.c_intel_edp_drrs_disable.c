#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_dp {TYPE_3__* attached_connector; } ;
struct intel_crtc_state {int /*<<< orphan*/  has_drrs; } ;
struct TYPE_8__ {scalar_t__ refresh_rate_type; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * dp; } ;
struct drm_i915_private {TYPE_4__ drrs; } ;
struct TYPE_6__ {TYPE_1__* fixed_mode; } ;
struct TYPE_7__ {TYPE_2__ panel; } ;
struct TYPE_5__ {int /*<<< orphan*/  vrefresh; } ;

/* Variables and functions */
 scalar_t__ DRRS_LOW_RR ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_set_drrs_state (struct drm_i915_private*,struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_edp_drrs_disable(struct intel_dp *intel_dp,
			    const struct intel_crtc_state *old_crtc_state)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);

	if (!old_crtc_state->has_drrs)
		return;

	mutex_lock(&dev_priv->drrs.mutex);
	if (!dev_priv->drrs.dp) {
		mutex_unlock(&dev_priv->drrs.mutex);
		return;
	}

	if (dev_priv->drrs.refresh_rate_type == DRRS_LOW_RR)
		intel_dp_set_drrs_state(dev_priv, old_crtc_state,
			intel_dp->attached_connector->panel.fixed_mode->vrefresh);

	dev_priv->drrs.dp = NULL;
	mutex_unlock(&dev_priv->drrs.mutex);

	cancel_delayed_work_sync(&dev_priv->drrs.work);
}