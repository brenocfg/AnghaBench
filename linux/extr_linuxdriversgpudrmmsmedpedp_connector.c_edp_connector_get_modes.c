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
struct msm_edp {int /*<<< orphan*/  ctrl; } ;
struct edp_connector {struct msm_edp* edp; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 int msm_edp_ctrl_get_panel_info (int /*<<< orphan*/ ,struct drm_connector*,struct edid**) ; 
 struct edp_connector* to_edp_connector (struct drm_connector*) ; 

__attribute__((used)) static int edp_connector_get_modes(struct drm_connector *connector)
{
	struct edp_connector *edp_connector = to_edp_connector(connector);
	struct msm_edp *edp = edp_connector->edp;

	struct edid *drm_edid = NULL;
	int ret = 0;

	DBG("");
	ret = msm_edp_ctrl_get_panel_info(edp->ctrl, connector, &drm_edid);
	if (ret)
		return ret;

	drm_connector_update_edid_property(connector, drm_edid);
	if (drm_edid)
		ret = drm_add_edid_modes(connector, drm_edid);

	return ret;
}