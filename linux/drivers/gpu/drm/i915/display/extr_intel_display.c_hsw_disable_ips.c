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
struct TYPE_3__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  ips_enabled; TYPE_1__ base; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_IPS_CONTROL ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPS_CTL ; 
 int /*<<< orphan*/  IPS_ENABLE ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sandybridge_pcode_write (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

void hsw_disable_ips(const struct intel_crtc_state *crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);

	if (!crtc_state->ips_enabled)
		return;

	if (IS_BROADWELL(dev_priv)) {
		WARN_ON(sandybridge_pcode_write(dev_priv, DISPLAY_IPS_CONTROL, 0));
		/*
		 * Wait for PCODE to finish disabling IPS. The BSpec specified
		 * 42ms timeout value leads to occasional timeouts so use 100ms
		 * instead.
		 */
		if (intel_de_wait_for_clear(dev_priv, IPS_CTL, IPS_ENABLE, 100))
			DRM_ERROR("Timed out waiting for IPS disable\n");
	} else {
		I915_WRITE(IPS_CTL, 0);
		POSTING_READ(IPS_CTL);
	}

	/* We need to wait for a vblank before we can disable the plane. */
	intel_wait_for_vblank(dev_priv, crtc->pipe);
}