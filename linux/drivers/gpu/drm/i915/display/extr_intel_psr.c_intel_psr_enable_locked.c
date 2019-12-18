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
struct intel_dp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct TYPE_5__ {int enabled; scalar_t__ psr2_enabled; int /*<<< orphan*/  pipe; scalar_t__ busy_frontbuffer_bits; struct intel_dp* dp; } ;
struct drm_i915_private {TYPE_2__ psr; } ;
struct TYPE_6__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ intel_psr2_enabled (struct drm_i915_private*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_psr_activate (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_sink (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_enable_source (struct intel_dp*,struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  intel_psr_setup_vsc (struct intel_dp*,struct intel_crtc_state const*) ; 
 TYPE_3__* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_psr_enable_locked(struct drm_i915_private *dev_priv,
				    const struct intel_crtc_state *crtc_state)
{
	struct intel_dp *intel_dp = dev_priv->psr.dp;

	WARN_ON(dev_priv->psr.enabled);

	dev_priv->psr.psr2_enabled = intel_psr2_enabled(dev_priv, crtc_state);
	dev_priv->psr.busy_frontbuffer_bits = 0;
	dev_priv->psr.pipe = to_intel_crtc(crtc_state->base.crtc)->pipe;

	DRM_DEBUG_KMS("Enabling PSR%s\n",
		      dev_priv->psr.psr2_enabled ? "2" : "1");
	intel_psr_setup_vsc(intel_dp, crtc_state);
	intel_psr_enable_sink(intel_dp);
	intel_psr_enable_source(intel_dp, crtc_state);
	dev_priv->psr.enabled = true;

	intel_psr_activate(intel_dp);
}