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
struct drm_plane {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  base; int /*<<< orphan*/  status; } ;
struct drm_encoder {int possible_crtcs; scalar_t__ possible_clones; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {unsigned int unit; int pref_active; int is_implicit; struct drm_plane cursor; struct drm_plane primary; int /*<<< orphan*/ * pref_mode; int /*<<< orphan*/  pref_height; int /*<<< orphan*/  pref_width; struct drm_connector connector; struct drm_encoder encoder; struct drm_crtc crtc; } ;
struct vmw_screen_object_unit {TYPE_1__ base; } ;
struct vmw_private {int /*<<< orphan*/  hotplug_mode_update_property; int /*<<< orphan*/  initial_height; int /*<<< orphan*/  initial_width; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  suggested_y_property; int /*<<< orphan*/  suggested_x_property; } ;
struct drm_device {TYPE_2__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VIRTUAL ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_VIRTUAL ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_CURSOR ; 
 int /*<<< orphan*/  DRM_PLANE_TYPE_PRIMARY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_connector_register (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_connector_unregister (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,struct drm_crtc*,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (struct drm_encoder*) ; 
 int drm_encoder_init (struct drm_device*,struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_enable_fb_damage_clips (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_screen_object_unit*) ; 
 struct vmw_screen_object_unit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_cursor_plane_formats ; 
 int /*<<< orphan*/  vmw_du_connector_detect (struct drm_connector*,int) ; 
 int /*<<< orphan*/  vmw_du_connector_reset (struct drm_connector*) ; 
 int /*<<< orphan*/  vmw_du_crtc_reset (struct drm_crtc*) ; 
 int /*<<< orphan*/  vmw_du_plane_reset (struct drm_plane*) ; 
 int /*<<< orphan*/  vmw_primary_plane_formats ; 
 int /*<<< orphan*/  vmw_screen_object_crtc_funcs ; 
 int /*<<< orphan*/  vmw_screen_object_encoder_funcs ; 
 int /*<<< orphan*/  vmw_sou_connector_funcs ; 
 int /*<<< orphan*/  vmw_sou_connector_helper_funcs ; 
 int /*<<< orphan*/  vmw_sou_crtc_helper_funcs ; 
 int /*<<< orphan*/  vmw_sou_cursor_funcs ; 
 int /*<<< orphan*/  vmw_sou_cursor_plane_helper_funcs ; 
 int /*<<< orphan*/  vmw_sou_plane_funcs ; 
 int /*<<< orphan*/  vmw_sou_primary_plane_helper_funcs ; 

__attribute__((used)) static int vmw_sou_init(struct vmw_private *dev_priv, unsigned unit)
{
	struct vmw_screen_object_unit *sou;
	struct drm_device *dev = dev_priv->dev;
	struct drm_connector *connector;
	struct drm_encoder *encoder;
	struct drm_plane *primary, *cursor;
	struct drm_crtc *crtc;
	int ret;

	sou = kzalloc(sizeof(*sou), GFP_KERNEL);
	if (!sou)
		return -ENOMEM;

	sou->base.unit = unit;
	crtc = &sou->base.crtc;
	encoder = &sou->base.encoder;
	connector = &sou->base.connector;
	primary = &sou->base.primary;
	cursor = &sou->base.cursor;

	sou->base.pref_active = (unit == 0);
	sou->base.pref_width = dev_priv->initial_width;
	sou->base.pref_height = dev_priv->initial_height;
	sou->base.pref_mode = NULL;

	/*
	 * Remove this after enabling atomic because property values can
	 * only exist in a state object
	 */
	sou->base.is_implicit = false;

	/* Initialize primary plane */
	vmw_du_plane_reset(primary);

	ret = drm_universal_plane_init(dev, &sou->base.primary,
				       0, &vmw_sou_plane_funcs,
				       vmw_primary_plane_formats,
				       ARRAY_SIZE(vmw_primary_plane_formats),
				       NULL, DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize primary plane");
		goto err_free;
	}

	drm_plane_helper_add(primary, &vmw_sou_primary_plane_helper_funcs);
	drm_plane_enable_fb_damage_clips(primary);

	/* Initialize cursor plane */
	vmw_du_plane_reset(cursor);

	ret = drm_universal_plane_init(dev, &sou->base.cursor,
			0, &vmw_sou_cursor_funcs,
			vmw_cursor_plane_formats,
			ARRAY_SIZE(vmw_cursor_plane_formats),
			NULL, DRM_PLANE_TYPE_CURSOR, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize cursor plane");
		drm_plane_cleanup(&sou->base.primary);
		goto err_free;
	}

	drm_plane_helper_add(cursor, &vmw_sou_cursor_plane_helper_funcs);

	vmw_du_connector_reset(connector);
	ret = drm_connector_init(dev, connector, &vmw_sou_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret) {
		DRM_ERROR("Failed to initialize connector\n");
		goto err_free;
	}

	drm_connector_helper_add(connector, &vmw_sou_connector_helper_funcs);
	connector->status = vmw_du_connector_detect(connector, true);

	ret = drm_encoder_init(dev, encoder, &vmw_screen_object_encoder_funcs,
			       DRM_MODE_ENCODER_VIRTUAL, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize encoder\n");
		goto err_free_connector;
	}

	(void) drm_connector_attach_encoder(connector, encoder);
	encoder->possible_crtcs = (1 << unit);
	encoder->possible_clones = 0;

	ret = drm_connector_register(connector);
	if (ret) {
		DRM_ERROR("Failed to register connector\n");
		goto err_free_encoder;
	}


	vmw_du_crtc_reset(crtc);
	ret = drm_crtc_init_with_planes(dev, crtc, &sou->base.primary,
					&sou->base.cursor,
					&vmw_screen_object_crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize CRTC\n");
		goto err_free_unregister;
	}

	drm_crtc_helper_add(crtc, &vmw_sou_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	drm_object_attach_property(&connector->base,
				   dev_priv->hotplug_mode_update_property, 1);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);
	return 0;

err_free_unregister:
	drm_connector_unregister(connector);
err_free_encoder:
	drm_encoder_cleanup(encoder);
err_free_connector:
	drm_connector_cleanup(connector);
err_free:
	kfree(sou);
	return ret;
}