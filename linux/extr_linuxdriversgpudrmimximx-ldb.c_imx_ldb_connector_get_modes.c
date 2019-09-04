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
struct imx_ldb_channel {int /*<<< orphan*/  mode; scalar_t__ mode_valid; scalar_t__ edid; scalar_t__ ddc; TYPE_2__* panel; } ;
struct drm_display_mode {int type; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* get_modes ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int EINVAL ; 
 struct imx_ldb_channel* con_to_imx_ldb_ch (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,scalar_t__) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,scalar_t__) ; 
 scalar_t__ drm_get_edid (struct drm_connector*,scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int imx_ldb_connector_get_modes(struct drm_connector *connector)
{
	struct imx_ldb_channel *imx_ldb_ch = con_to_imx_ldb_ch(connector);
	int num_modes = 0;

	if (imx_ldb_ch->panel && imx_ldb_ch->panel->funcs &&
	    imx_ldb_ch->panel->funcs->get_modes) {
		num_modes = imx_ldb_ch->panel->funcs->get_modes(imx_ldb_ch->panel);
		if (num_modes > 0)
			return num_modes;
	}

	if (!imx_ldb_ch->edid && imx_ldb_ch->ddc)
		imx_ldb_ch->edid = drm_get_edid(connector, imx_ldb_ch->ddc);

	if (imx_ldb_ch->edid) {
		drm_connector_update_edid_property(connector,
							imx_ldb_ch->edid);
		num_modes = drm_add_edid_modes(connector, imx_ldb_ch->edid);
	}

	if (imx_ldb_ch->mode_valid) {
		struct drm_display_mode *mode;

		mode = drm_mode_create(connector->dev);
		if (!mode)
			return -EINVAL;
		drm_mode_copy(mode, &imx_ldb_ch->mode);
		mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, mode);
		num_modes++;
	}

	return num_modes;
}