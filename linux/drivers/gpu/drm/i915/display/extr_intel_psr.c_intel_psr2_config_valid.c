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
struct intel_dp {int dummy; } ;
struct TYPE_7__ {scalar_t__ compression_enable; } ;
struct TYPE_5__ {int crtc_hdisplay; int crtc_vdisplay; } ;
struct TYPE_6__ {TYPE_1__ adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ crc_enabled; TYPE_3__ dsc_params; TYPE_2__ base; } ;
struct TYPE_8__ {int su_x_granularity; int /*<<< orphan*/  sink_psr2_support; } ;
struct drm_i915_private {TYPE_4__ psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 

__attribute__((used)) static bool intel_psr2_config_valid(struct intel_dp *intel_dp,
				    struct intel_crtc_state *crtc_state)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	int crtc_hdisplay = crtc_state->base.adjusted_mode.crtc_hdisplay;
	int crtc_vdisplay = crtc_state->base.adjusted_mode.crtc_vdisplay;
	int psr_max_h = 0, psr_max_v = 0;

	if (!dev_priv->psr.sink_psr2_support)
		return false;

	/*
	 * DSC and PSR2 cannot be enabled simultaneously. If a requested
	 * resolution requires DSC to be enabled, priority is given to DSC
	 * over PSR2.
	 */
	if (crtc_state->dsc_params.compression_enable) {
		DRM_DEBUG_KMS("PSR2 cannot be enabled since DSC is enabled\n");
		return false;
	}

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv)) {
		psr_max_h = 4096;
		psr_max_v = 2304;
	} else if (IS_GEN(dev_priv, 9)) {
		psr_max_h = 3640;
		psr_max_v = 2304;
	}

	if (crtc_hdisplay > psr_max_h || crtc_vdisplay > psr_max_v) {
		DRM_DEBUG_KMS("PSR2 not enabled, resolution %dx%d > max supported %dx%d\n",
			      crtc_hdisplay, crtc_vdisplay,
			      psr_max_h, psr_max_v);
		return false;
	}

	/*
	 * HW sends SU blocks of size four scan lines, which means the starting
	 * X coordinate and Y granularity requirements will always be met. We
	 * only need to validate the SU block width is a multiple of
	 * x granularity.
	 */
	if (crtc_hdisplay % dev_priv->psr.su_x_granularity) {
		DRM_DEBUG_KMS("PSR2 not enabled, hdisplay(%d) not multiple of %d\n",
			      crtc_hdisplay, dev_priv->psr.su_x_granularity);
		return false;
	}

	if (crtc_state->crc_enabled) {
		DRM_DEBUG_KMS("PSR2 not enabled because it would inhibit pipe CRC calculation\n");
		return false;
	}

	return true;
}