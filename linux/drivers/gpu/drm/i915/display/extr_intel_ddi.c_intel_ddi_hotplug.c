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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_mst; } ;
struct intel_digital_port {TYPE_2__ dp; } ;
struct TYPE_3__ {scalar_t__ connector_type; } ;
struct intel_connector {TYPE_1__ base; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
typedef  enum intel_hotplug_state { ____Placeholder_intel_hotplug_state } intel_hotplug_state ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONNECTOR_HDMIA ; 
 int EDEADLK ; 
 int INTEL_HOTPLUG_RETRY ; 
 int INTEL_HOTPLUG_UNCHANGED ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 struct intel_digital_port* enc_to_dig_port (int /*<<< orphan*/ *) ; 
 int intel_dp_retrain_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 
 int intel_encoder_hotplug (struct intel_encoder*,struct intel_connector*,int) ; 
 int intel_hdmi_reset_link (struct intel_encoder*,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static enum intel_hotplug_state
intel_ddi_hotplug(struct intel_encoder *encoder,
		  struct intel_connector *connector,
		  bool irq_received)
{
	struct intel_digital_port *dig_port = enc_to_dig_port(&encoder->base);
	struct drm_modeset_acquire_ctx ctx;
	enum intel_hotplug_state state;
	int ret;

	state = intel_encoder_hotplug(encoder, connector, irq_received);

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

	/*
	 * Unpowered type-c dongles can take some time to boot and be
	 * responsible, so here giving some time to those dongles to power up
	 * and then retrying the probe.
	 *
	 * On many platforms the HDMI live state signal is known to be
	 * unreliable, so we can't use it to detect if a sink is connected or
	 * not. Instead we detect if it's connected based on whether we can
	 * read the EDID or not. That in turn has a problem during disconnect,
	 * since the HPD interrupt may be raised before the DDC lines get
	 * disconnected (due to how the required length of DDC vs. HPD
	 * connector pins are specified) and so we'll still be able to get a
	 * valid EDID. To solve this schedule another detection cycle if this
	 * time around we didn't detect any change in the sink's connection
	 * status.
	 */
	if (state == INTEL_HOTPLUG_UNCHANGED && irq_received &&
	    !dig_port->dp.is_mst)
		state = INTEL_HOTPLUG_RETRY;

	return state;
}