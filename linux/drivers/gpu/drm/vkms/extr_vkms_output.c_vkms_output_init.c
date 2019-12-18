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
struct drm_crtc {int dummy; } ;
struct drm_encoder {int possible_crtcs; } ;
struct drm_connector {int dummy; } ;
struct vkms_output {struct drm_crtc crtc; struct drm_encoder encoder; struct drm_connector connector; } ;
struct drm_device {int dummy; } ;
struct vkms_device {struct drm_device drm; struct vkms_output output; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int PTR_ERR (struct drm_plane*) ; 
 int drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 scalar_t__ enable_cursor ; 
 int /*<<< orphan*/  vkms_conn_helper_funcs ; 
 int /*<<< orphan*/  vkms_connector_funcs ; 
 int vkms_crtc_init (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*) ; 
 int /*<<< orphan*/  vkms_encoder_funcs ; 
 struct drm_plane* vkms_plane_init (struct vkms_device*,int /*<<< orphan*/ ,int) ; 

int vkms_output_init(struct vkms_device *vkmsdev, int index)
{
	struct vkms_output *output = &vkmsdev->output;
	struct drm_device *dev = &vkmsdev->drm;
	struct drm_connector *connector = &output->connector;
	struct drm_encoder *encoder = &output->encoder;
	struct drm_crtc *crtc = &output->crtc;
	struct drm_plane *primary, *cursor = NULL;
	int ret;

	primary = vkms_plane_init(vkmsdev, DRM_PLANE_TYPE_PRIMARY, index);
	if (IS_ERR(primary))
		return PTR_ERR(primary);

	if (enable_cursor) {
		cursor = vkms_plane_init(vkmsdev, DRM_PLANE_TYPE_CURSOR, index);
		if (IS_ERR(cursor)) {
			ret = PTR_ERR(cursor);
			goto err_cursor;
		}
	}

	ret = vkms_crtc_init(dev, crtc, primary, cursor);
	if (ret)
		goto err_crtc;

	ret = drm_connector_init(dev, connector, &vkms_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret) {
		DRM_ERROR("Failed to init connector\n");
		goto err_connector;
	}

	drm_connector_helper_add(connector, &vkms_conn_helper_funcs);

	ret = drm_encoder_init(dev, encoder, &vkms_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, NULL);
	if (ret) {
		DRM_ERROR("Failed to init encoder\n");
		goto err_encoder;
	}
	encoder->possible_crtcs = 1;

	ret = drm_connector_attach_encoder(connector, encoder);
	if (ret) {
		DRM_ERROR("Failed to attach connector to encoder\n");
		goto err_attach;
	}

	drm_mode_config_reset(dev);

	return 0;

err_attach:
	drm_encoder_cleanup(encoder);

err_encoder:
	drm_connector_cleanup(connector);

err_connector:
	drm_crtc_cleanup(crtc);

err_crtc:
	if (enable_cursor)
		drm_plane_cleanup(cursor);

err_cursor:
	drm_plane_cleanup(primary);

	return ret;
}