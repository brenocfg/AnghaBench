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
struct vbox_crtc {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  base; scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; } ;
struct vbox_connector {struct vbox_crtc* vbox_crtc; struct drm_connector base; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  suggested_y_property; int /*<<< orphan*/  suggested_x_property; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_VGA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_init (struct drm_device*,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_create_suggested_offset_properties (struct drm_device*) ; 
 int /*<<< orphan*/  drm_object_attach_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vbox_connector* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vbox_connector_funcs ; 
 int /*<<< orphan*/  vbox_connector_helper_funcs ; 

__attribute__((used)) static int vbox_connector_init(struct drm_device *dev,
			       struct vbox_crtc *vbox_crtc,
			       struct drm_encoder *encoder)
{
	struct vbox_connector *vbox_connector;
	struct drm_connector *connector;

	vbox_connector = kzalloc(sizeof(*vbox_connector), GFP_KERNEL);
	if (!vbox_connector)
		return -ENOMEM;

	connector = &vbox_connector->base;
	vbox_connector->vbox_crtc = vbox_crtc;

	drm_connector_init(dev, connector, &vbox_connector_funcs,
			   DRM_MODE_CONNECTOR_VGA);
	drm_connector_helper_add(connector, &vbox_connector_helper_funcs);

	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_mode_create_suggested_offset_properties(dev);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_x_property, 0);
	drm_object_attach_property(&connector->base,
				   dev->mode_config.suggested_y_property, 0);

	drm_connector_attach_encoder(connector, encoder);

	return 0;
}