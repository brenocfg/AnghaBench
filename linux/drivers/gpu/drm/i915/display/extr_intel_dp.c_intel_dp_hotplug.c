#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_encoder {int dummy; } ;
struct intel_connector {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
typedef  enum intel_hotplug_state { ____Placeholder_intel_hotplug_state } intel_hotplug_state ;

/* Variables and functions */
 int EDEADLK ; 
 int INTEL_HOTPLUG_RETRY ; 
 int INTEL_HOTPLUG_UNCHANGED ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int intel_dp_retrain_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 
 int intel_encoder_hotplug (struct intel_encoder*,struct intel_connector*,int) ; 

__attribute__((used)) static enum intel_hotplug_state
intel_dp_hotplug(struct intel_encoder *encoder,
		 struct intel_connector *connector,
		 bool irq_received)
{
	struct drm_modeset_acquire_ctx ctx;
	enum intel_hotplug_state state;
	int ret;

	state = intel_encoder_hotplug(encoder, connector, irq_received);

	drm_modeset_acquire_init(&ctx, 0);

	for (;;) {
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

	/*
	 * Keeping it consistent with intel_ddi_hotplug() and
	 * intel_hdmi_hotplug().
	 */
	if (state == INTEL_HOTPLUG_UNCHANGED && irq_received)
		state = INTEL_HOTPLUG_RETRY;

	return state;
}