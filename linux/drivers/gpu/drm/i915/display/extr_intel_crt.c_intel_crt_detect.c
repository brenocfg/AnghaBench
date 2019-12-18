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
struct intel_load_detect_pipe {int dummy; } ;
struct intel_encoder {int /*<<< orphan*/  power_domain; } ;
struct intel_crt {struct intel_encoder base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int status; TYPE_2__* state; int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_8__ {scalar_t__ load_detect_test; } ;
struct TYPE_7__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_6__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 scalar_t__ I915_HAS_HOTPLUG (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int connector_status_unknown ; 
 scalar_t__ dmi_check_system (int /*<<< orphan*/ ) ; 
 TYPE_4__ i915_modparams ; 
 struct intel_crt* intel_attached_crt (struct drm_connector*) ; 
 scalar_t__ intel_crt_detect_ddc (struct drm_connector*) ; 
 scalar_t__ intel_crt_detect_hotplug (struct drm_connector*) ; 
 int intel_crt_load_detect (struct intel_crt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_flush_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int intel_get_load_detect_pipe (struct drm_connector*,int /*<<< orphan*/ *,struct intel_load_detect_pipe*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  intel_release_load_detect_pipe (struct drm_connector*,struct intel_load_detect_pipe*,struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  intel_spurious_crt_detect ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_crt_detect(struct drm_connector *connector,
		 struct drm_modeset_acquire_ctx *ctx,
		 bool force)
{
	struct drm_i915_private *dev_priv = to_i915(connector->dev);
	struct intel_crt *crt = intel_attached_crt(connector);
	struct intel_encoder *intel_encoder = &crt->base;
	intel_wakeref_t wakeref;
	int status, ret;
	struct intel_load_detect_pipe tmp;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s] force=%d\n",
		      connector->base.id, connector->name,
		      force);

	if (i915_modparams.load_detect_test) {
		wakeref = intel_display_power_get(dev_priv,
						  intel_encoder->power_domain);
		goto load_detect;
	}

	/* Skip machines without VGA that falsely report hotplug events */
	if (dmi_check_system(intel_spurious_crt_detect))
		return connector_status_disconnected;

	wakeref = intel_display_power_get(dev_priv,
					  intel_encoder->power_domain);

	if (I915_HAS_HOTPLUG(dev_priv)) {
		/* We can not rely on the HPD pin always being correctly wired
		 * up, for example many KVM do not pass it through, and so
		 * only trust an assertion that the monitor is connected.
		 */
		if (intel_crt_detect_hotplug(connector)) {
			DRM_DEBUG_KMS("CRT detected via hotplug\n");
			status = connector_status_connected;
			goto out;
		} else
			DRM_DEBUG_KMS("CRT not detected via hotplug\n");
	}

	if (intel_crt_detect_ddc(connector)) {
		status = connector_status_connected;
		goto out;
	}

	/* Load detection is broken on HPD capable machines. Whoever wants a
	 * broken monitor (without edid) to work behind a broken kvm (that fails
	 * to have the right resistors for HP detection) needs to fix this up.
	 * For now just bail out. */
	if (I915_HAS_HOTPLUG(dev_priv)) {
		status = connector_status_disconnected;
		goto out;
	}

load_detect:
	if (!force) {
		status = connector->status;
		goto out;
	}

	/* for pre-945g platforms use load detect */
	ret = intel_get_load_detect_pipe(connector, NULL, &tmp, ctx);
	if (ret > 0) {
		if (intel_crt_detect_ddc(connector))
			status = connector_status_connected;
		else if (INTEL_GEN(dev_priv) < 4)
			status = intel_crt_load_detect(crt,
				to_intel_crtc(connector->state->crtc)->pipe);
		else if (i915_modparams.load_detect_test)
			status = connector_status_disconnected;
		else
			status = connector_status_unknown;
		intel_release_load_detect_pipe(connector, &tmp, ctx);
	} else if (ret == 0) {
		status = connector_status_unknown;
	} else {
		status = ret;
	}

out:
	intel_display_power_put(dev_priv, intel_encoder->power_domain, wakeref);

	/*
	 * Make sure the refs for power wells enabled during detect are
	 * dropped to avoid a new detect cycle triggered by HPD polling.
	 */
	intel_display_power_flush_work(dev_priv);

	return status;
}