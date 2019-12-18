#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  suggested_y_property; int /*<<< orphan*/  suggested_x_property; } ;
struct TYPE_9__ {TYPE_3__ mode_config; } ;
struct vbox_private {TYPE_4__ ddev; int /*<<< orphan*/  guest_pool; } ;
struct TYPE_6__ {int width; int height; } ;
struct vbox_connector {TYPE_2__* vbox_crtc; TYPE_1__ mode_hint; } ;
struct drm_display_mode {int /*<<< orphan*/  type; } ;
struct drm_connector {int /*<<< orphan*/  base; TYPE_5__* dev; } ;
struct TYPE_10__ {struct vbox_private* dev_private; } ;
struct TYPE_7__ {scalar_t__ crtc_id; int x_hint; int y_hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 scalar_t__ GUEST_HEAP_OFFSET (struct vbox_private*) ; 
 scalar_t__ HOST_FLAGS_OFFSET ; 
 unsigned int drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 struct drm_display_mode* drm_cvt_mode (TYPE_5__*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_object_property_set_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hgsmi_report_flags_location (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vbox_connector* to_vbox_connector (struct drm_connector*) ; 
 int /*<<< orphan*/  vbox_report_caps (struct vbox_private*) ; 
 int /*<<< orphan*/  vbox_set_edid (struct drm_connector*,int,int) ; 

__attribute__((used)) static int vbox_get_modes(struct drm_connector *connector)
{
	struct vbox_connector *vbox_connector = NULL;
	struct drm_display_mode *mode = NULL;
	struct vbox_private *vbox = NULL;
	unsigned int num_modes = 0;
	int preferred_width, preferred_height;

	vbox_connector = to_vbox_connector(connector);
	vbox = connector->dev->dev_private;

	hgsmi_report_flags_location(vbox->guest_pool, GUEST_HEAP_OFFSET(vbox) +
				    HOST_FLAGS_OFFSET);
	if (vbox_connector->vbox_crtc->crtc_id == 0)
		vbox_report_caps(vbox);

	num_modes = drm_add_modes_noedid(connector, 2560, 1600);
	preferred_width = vbox_connector->mode_hint.width ?
			  vbox_connector->mode_hint.width : 1024;
	preferred_height = vbox_connector->mode_hint.height ?
			   vbox_connector->mode_hint.height : 768;
	mode = drm_cvt_mode(connector->dev, preferred_width, preferred_height,
			    60, false, false, false);
	if (mode) {
		mode->type |= DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		++num_modes;
	}
	vbox_set_edid(connector, preferred_width, preferred_height);

	if (vbox_connector->vbox_crtc->x_hint != -1)
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_x_property,
			vbox_connector->vbox_crtc->x_hint);
	else
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_x_property, 0);

	if (vbox_connector->vbox_crtc->y_hint != -1)
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_y_property,
			vbox_connector->vbox_crtc->y_hint);
	else
		drm_object_property_set_value(&connector->base,
			vbox->ddev.mode_config.suggested_y_property, 0);

	return num_modes;
}