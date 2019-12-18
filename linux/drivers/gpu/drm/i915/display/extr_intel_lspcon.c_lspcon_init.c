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
struct intel_lspcon {int active; int /*<<< orphan*/  mode; } ;
struct intel_dp {TYPE_3__* attached_connector; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; struct intel_lspcon lspcon; struct intel_dp dp; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int ycbcr_420_allowed; } ;
struct TYPE_6__ {struct drm_connector base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_LSPCON_MODE_INVALID ; 
 int /*<<< orphan*/  HAS_LSPCON (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_dp_read_dpcd (struct intel_dp*) ; 
 int /*<<< orphan*/  lspcon_detect_vendor (struct intel_lspcon*) ; 
 int /*<<< orphan*/  lspcon_probe (struct intel_lspcon*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

bool lspcon_init(struct intel_digital_port *intel_dig_port)
{
	struct intel_dp *dp = &intel_dig_port->dp;
	struct intel_lspcon *lspcon = &intel_dig_port->lspcon;
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_connector *connector = &dp->attached_connector->base;

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

	if (!intel_dp_read_dpcd(dp)) {
		DRM_ERROR("LSPCON DPCD read failed\n");
		return false;
	}

	if (!lspcon_detect_vendor(lspcon)) {
		DRM_ERROR("LSPCON vendor detection failed\n");
		return false;
	}

	connector->ycbcr_420_allowed = true;
	lspcon->active = true;
	DRM_DEBUG_KMS("Success: LSPCON init\n");
	return true;
}