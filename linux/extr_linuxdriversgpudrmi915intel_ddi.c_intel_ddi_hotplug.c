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
struct intel_encoder {int dummy; } ;
struct TYPE_2__ {scalar_t__ connector_type; } ;
struct intel_connector {TYPE_1__ base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_HDMIA ; 
 int EDEADLK ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int intel_dp_retrain_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 
 int intel_encoder_hotplug (struct intel_encoder*,struct intel_connector*) ; 
 int intel_hdmi_reset_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static bool intel_ddi_hotplug(struct intel_encoder *encoder,
			      struct intel_connector *connector)
{
	struct drm_modeset_acquire_ctx ctx;
	bool changed;
	int ret;

	changed = intel_encoder_hotplug(encoder, connector);

	drm_modeset_acquire_init(&ctx, 0);

	for (;;) {
		if (connector->base.connector_type == DRM_MODE_CONNECTOR_HDMIA)
			ret = intel_hdmi_reset_link(encoder, &ctx);
		else
			ret = intel_dp_retrain_link(encoder, &ctx);

		if (ret == -EDEADLK) {
			drm_modeset_backoff(&ctx);
			continue;
		}

		break;
	}

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
	WARN(ret, "Acquiring modeset locks failed with %i\n", ret);

	return changed;
}