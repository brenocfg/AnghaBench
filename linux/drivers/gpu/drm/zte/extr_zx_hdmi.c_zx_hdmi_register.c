#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  polled; } ;
struct drm_encoder {int /*<<< orphan*/  possible_crtcs; } ;
struct zx_hdmi {TYPE_1__ connector; struct drm_encoder encoder; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_TMDS ; 
 int /*<<< orphan*/  VOU_CRTC_MASK ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_1__*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_encoder_helper_add (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zx_hdmi_connector_funcs ; 
 int /*<<< orphan*/  zx_hdmi_connector_helper_funcs ; 
 int /*<<< orphan*/  zx_hdmi_encoder_funcs ; 
 int /*<<< orphan*/  zx_hdmi_encoder_helper_funcs ; 

__attribute__((used)) static int zx_hdmi_register(struct drm_device *drm, struct zx_hdmi *hdmi)
{
	struct drm_encoder *encoder = &hdmi->encoder;

	encoder->possible_crtcs = VOU_CRTC_MASK;

	drm_encoder_init(drm, encoder, &zx_hdmi_encoder_funcs,
			 DRM_MODE_ENCODER_TMDS, NULL);
	drm_encoder_helper_add(encoder, &zx_hdmi_encoder_helper_funcs);

	hdmi->connector.polled = DRM_CONNECTOR_POLL_HPD;

	drm_connector_init(drm, &hdmi->connector, &zx_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_HDMIA);
	drm_connector_helper_add(&hdmi->connector,
				 &zx_hdmi_connector_helper_funcs);

	drm_connector_attach_encoder(&hdmi->connector, encoder);

	return 0;
}