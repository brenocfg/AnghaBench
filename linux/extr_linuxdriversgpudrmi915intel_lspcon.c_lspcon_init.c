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
struct intel_lspcon {int active; scalar_t__ mode; } ;
struct intel_dp {int /*<<< orphan*/  dpcd; int /*<<< orphan*/  desc; int /*<<< orphan*/  aux; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; struct intel_lspcon lspcon; struct intel_dp dp; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ DRM_LSPCON_MODE_INVALID ; 
 scalar_t__ DRM_LSPCON_MODE_PCON ; 
 int /*<<< orphan*/  HAS_LSPCON (struct drm_i915_private*) ; 
 int /*<<< orphan*/  drm_dp_is_branch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_read_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_read_dpcd (struct intel_dp*) ; 
 scalar_t__ lspcon_change_mode (struct intel_lspcon*,scalar_t__) ; 
 int /*<<< orphan*/  lspcon_probe (struct intel_lspcon*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

bool lspcon_init(struct intel_digital_port *intel_dig_port)
{
	struct intel_dp *dp = &intel_dig_port->dp;
	struct intel_lspcon *lspcon = &intel_dig_port->lspcon;
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (!HAS_LSPCON(dev_priv)) {
		DRM_ERROR("LSPCON is not supported on this platform\n");
		return false;
	}

	lspcon->active = false;
	lspcon->mode = DRM_LSPCON_MODE_INVALID;

	if (!lspcon_probe(lspcon)) {
		DRM_ERROR("Failed to probe lspcon\n");
		return false;
	}

	/*
	* In the SW state machine, lets Put LSPCON in PCON mode only.
	* In this way, it will work with both HDMI 1.4 sinks as well as HDMI
	* 2.0 sinks.
	*/
	if (lspcon->active && lspcon->mode != DRM_LSPCON_MODE_PCON) {
		if (lspcon_change_mode(lspcon, DRM_LSPCON_MODE_PCON) < 0) {
			DRM_ERROR("LSPCON mode change to PCON failed\n");
			return false;
		}
	}

	if (!intel_dp_read_dpcd(dp)) {
		DRM_ERROR("LSPCON DPCD read failed\n");
		return false;
	}

	drm_dp_read_desc(&dp->aux, &dp->desc, drm_dp_is_branch(dp->dpcd));

	DRM_DEBUG_KMS("Success: LSPCON init\n");
	return true;
}