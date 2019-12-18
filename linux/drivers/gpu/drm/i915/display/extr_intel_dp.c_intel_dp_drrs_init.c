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
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_3__ base; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  refresh_rate_type; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; } ;
struct TYPE_4__ {scalar_t__ drrs_type; } ;
struct drm_i915_private {TYPE_2__ drrs; TYPE_1__ vbt; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRRS_HIGH_RR ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ SEAMLESS_DRRS_SUPPORT ; 
 int /*<<< orphan*/  intel_edp_drrs_downclock_work ; 
 struct drm_display_mode* intel_panel_edid_downclock_mode (struct intel_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_display_mode *
intel_dp_drrs_init(struct intel_connector *connector,
		   struct drm_display_mode *fixed_mode)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct drm_display_mode *downclock_mode = NULL;

	INIT_DELAYED_WORK(&dev_priv->drrs.work, intel_edp_drrs_downclock_work);
	mutex_init(&dev_priv->drrs.mutex);

	if (INTEL_GEN(dev_priv) <= 6) {
		DRM_DEBUG_KMS("DRRS supported for Gen7 and above\n");
		return NULL;
	}

	if (dev_priv->vbt.drrs_type != SEAMLESS_DRRS_SUPPORT) {
		DRM_DEBUG_KMS("VBT doesn't support DRRS\n");
		return NULL;
	}

	downclock_mode = intel_panel_edid_downclock_mode(connector, fixed_mode);
	if (!downclock_mode) {
		DRM_DEBUG_KMS("Downclock mode is not found. DRRS not supported\n");
		return NULL;
	}

	dev_priv->drrs.type = dev_priv->vbt.drrs_type;

	dev_priv->drrs.refresh_rate_type = DRRS_HIGH_RR;
	DRM_DEBUG_KMS("seamless DRRS supported for eDP panel.\n");
	return downclock_mode;
}