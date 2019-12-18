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
struct vmw_private {int /*<<< orphan*/  implicit_placement_property; int /*<<< orphan*/  hotplug_mode_update_property; int /*<<< orphan*/  initial_height; int /*<<< orphan*/  initial_width; struct drm_device* dev; } ;
struct drm_plane {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  base; int /*<<< orphan*/  status; } ;
struct drm_encoder {int possible_crtcs; scalar_t__ possible_clones; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {unsigned int unit; int pref_active; int is_implicit; struct drm_plane cursor; struct drm_plane primary; int /*<<< orphan*/ * pref_mode; int /*<<< orphan*/  pref_height; int /*<<< orphan*/  pref_width; struct drm_connector connector; struct drm_encoder encoder; struct drm_crtc crtc; } ;
struct vmw_legacy_display_unit {TYPE_1__ base; int /*<<< orphan*/  active; } ;
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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  drm_plane_helper_add (struct drm_plane*,int /*<<< orphan*/ *) ; 
 int drm_universal_plane_init (struct drm_device*,struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_legacy_display_unit*) ; 
 struct vmw_legacy_display_unit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_cursor_plane_formats ; 
 int /*<<< orphan*/  vmw_du_connector_detect (struct drm_connector*,int) ; 
 int /*<<< orphan*/  vmw_du_connector_reset (struct drm_connector*) ; 
 int /*<<< orphan*/  vmw_du_crtc_reset (struct drm_crtc*) ; 
 int /*<<< orphan*/  vmw_du_plane_reset (struct drm_plane*) ; 
 int /*<<< orphan*/  vmw_ldu_connector_helper_funcs ; 
 int /*<<< orphan*/  vmw_ldu_crtc_helper_funcs ; 
 int /*<<< orphan*/  vmw_ldu_cursor_funcs ; 
 int /*<<< orphan*/  vmw_ldu_cursor_plane_helper_funcs ; 
 int /*<<< orphan*/  vmw_ldu_plane_funcs ; 
 int /*<<< orphan*/  vmw_ldu_primary_plane_helper_funcs ; 
 int /*<<< orphan*/  vmw_legacy_connector_funcs ; 
 int /*<<< orphan*/  vmw_legacy_crtc_funcs ; 
 int /*<<< orphan*/  vmw_legacy_encoder_funcs ; 
 int /*<<< orphan*/  vmw_primary_plane_formats ; 

__attribute__((used)) static int vmw_ldu_init(struct vmw_private *dev_priv, unsigned unit)
{
	struct vmw_legacy_display_unit *ldu;
	struct drm_device *dev = dev_priv->dev;
	struct drm_connector *connector;
	struct drm_encoder *encoder;
	struct drm_plane *primary, *cursor;
	struct drm_crtc *crtc;
	int ret;

	ldu = kzalloc(sizeof(*ldu), GFP_KERNEL);
	if (!ldu)
		return -ENOMEM;

	ldu->base.unit = unit;
	crtc = &ldu->base.crtc;
	encoder = &ldu->base.encoder;
	connector = &ldu->base.connector;
	primary = &ldu->base.primary;
	cursor = &ldu->base.cursor;

	INIT_LIST_HEAD(&ldu->active);

	ldu->base.pref_active = (unit == 0);
	ldu->base.pref_width = dev_priv->initial_width;
	ldu->base.pref_height = dev_priv->initial_height;
	ldu->base.pref_mode = NULL;

	/*
	 * Remove this after enabling atomic because property values can
	 * only exist in a state object
	 */
	ldu->base.is_implicit = true;

	/* Initialize primary plane */
	vmw_du_plane_reset(primary);

	ret = drm_universal_plane_init(dev, &ldu->base.primary,
				       0, &vmw_ldu_plane_funcs,
				       vmw_primary_plane_formats,
				       ARRAY_SIZE(vmw_primary_plane_formats),
				       NULL, DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize primary plane");
		goto err_free;
	}

	drm_plane_helper_add(primary, &vmw_ldu_primary_plane_helper_funcs);

	/* Initialize cursor plane */
	vmw_du_plane_reset(cursor);

	ret = drm_universal_plane_init(dev, &ldu->base.cursor,
			0, &vmw_ldu_cursor_funcs,
			vmw_cursor_plane_formats,
			ARRAY_SIZE(vmw_cursor_plane_formats),
			NULL, DRM_PLANE_TYPE_CURSOR, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize cursor plane");
		drm_plane_cleanup(&ldu->base.primary);
		goto err_free;
	}

	drm_plane_helper_add(cursor, &vmw_ldu_cursor_plane_helper_funcs);

	vmw_du_connector_reset(connector);
	ret = drm_connector_init(dev, connector, &vmw_legacy_connector_funcs,
				 DRM_MODE_CONNECTOR_VIRTUAL);
	if (ret) {
		DRM_ERROR("Failed to initialize connector\n");
		goto err_free;
	}

	drm_connector_helper_add(connector, &vmw_ldu_connector_helper_funcs);
	connector->status = vmw_du_connector_detect(connector, true);

	ret = drm_encoder_init(dev, encoder, &vmw_legacy_encoder_funcs,
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
	ret = drm_crtc_init_with_planes(dev, crtc, &ldu->base.primary,
					&ldu->base.cursor,
					&vmw_legacy_crtc_funcs, NULL);
	if (ret) {
		DRM_ERROR("Failed to initialize CRTC\n");
		goto err_free_unregister;
	}

	drm_crtc_helper_add(crtc, &vmw_ldu_crtc_helper_funcs);

	drm_mode_crtc_set_gamma_size(crtc, 256);

	drm_object_attach_property(&connector->base,
				   dev_priv->hotplug_mode_update_property, 1);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);
	if (dev_priv->implicit_placement_property)
		drm_object_attach_property
			(&connector->base,
			 dev_priv->implicit_placement_property,
			 1);

	return 0;

err_free_unregister:
	drm_connector_unregister(connector);
err_free_encoder:
	drm_encoder_cleanup(encoder);
err_free_connector:
	drm_connector_cleanup(connector);
err_free:
	kfree(ldu);
	return ret;
}