#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct imx_parallel_display {int /*<<< orphan*/  mode; int /*<<< orphan*/  bus_flags; scalar_t__ edid; TYPE_3__* panel; TYPE_1__* dev; } ;
struct drm_display_mode {int type; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {TYPE_2__* funcs; } ;
struct TYPE_5__ {int (* get_modes ) (TYPE_3__*) ;} ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int DRM_MODE_TYPE_DRIVER ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int EINVAL ; 
 int /*<<< orphan*/  OF_USE_NATIVE_MODE ; 
 struct imx_parallel_display* con_to_imxpd (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,scalar_t__) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,scalar_t__) ; 
 int /*<<< orphan*/  drm_mode_copy (struct drm_display_mode*,int /*<<< orphan*/ *) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int of_get_drm_display_mode (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*) ; 

__attribute__((used)) static int imx_pd_connector_get_modes(struct drm_connector *connector)
{
	struct imx_parallel_display *imxpd = con_to_imxpd(connector);
	struct device_node *np = imxpd->dev->of_node;
	int num_modes = 0;

	if (imxpd->panel && imxpd->panel->funcs &&
	    imxpd->panel->funcs->get_modes) {
		num_modes = imxpd->panel->funcs->get_modes(imxpd->panel);
		if (num_modes > 0)
			return num_modes;
	}

	if (imxpd->edid) {
		drm_connector_update_edid_property(connector, imxpd->edid);
		num_modes = drm_add_edid_modes(connector, imxpd->edid);
	}

	if (np) {
		struct drm_display_mode *mode = drm_mode_create(connector->dev);
		int ret;

		if (!mode)
			return -EINVAL;

		ret = of_get_drm_display_mode(np, &imxpd->mode,
					      &imxpd->bus_flags,
					      OF_USE_NATIVE_MODE);
		if (ret)
			return ret;

		drm_mode_copy(mode, &imxpd->mode);
		mode->type |= DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
		drm_mode_probed_add(connector, mode);
		num_modes++;
	}

	return num_modes;
}