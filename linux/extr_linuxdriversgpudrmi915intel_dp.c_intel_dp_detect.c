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
struct intel_dp {int detect_done; int /*<<< orphan*/  attached_connector; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct drm_connector {int status; TYPE_1__* state; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,struct drm_modeset_acquire_ctx*) ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 int intel_dp_long_pulse (int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static int
intel_dp_detect(struct drm_connector *connector,
		struct drm_modeset_acquire_ctx *ctx,
		bool force)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);
	int status = connector->status;

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	/* If full detect is not performed yet, do a full detect */
	if (!intel_dp->detect_done) {
		struct drm_crtc *crtc;
		int ret;

		crtc = connector->state->crtc;
		if (crtc) {
			ret = drm_modeset_lock(&crtc->mutex, ctx);
			if (ret)
				return ret;
		}

		status = intel_dp_long_pulse(intel_dp->attached_connector, ctx);
	}

	intel_dp->detect_done = false;

	return status;
}