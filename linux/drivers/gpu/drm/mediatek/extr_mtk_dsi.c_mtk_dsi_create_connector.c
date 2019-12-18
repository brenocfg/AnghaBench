#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dpms; } ;
struct mtk_dsi {TYPE_1__ conn; scalar_t__ panel; int /*<<< orphan*/  encoder; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_connector_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_panel_attach (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  mtk_dsi_connector_funcs ; 
 int /*<<< orphan*/  mtk_dsi_connector_helper_funcs ; 

__attribute__((used)) static int mtk_dsi_create_connector(struct drm_device *drm, struct mtk_dsi *dsi)
{
	int ret;

	ret = drm_connector_init(drm, &dsi->conn, &mtk_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	if (ret) {
		DRM_ERROR("Failed to connector init to drm\n");
		return ret;
	}

	drm_connector_helper_add(&dsi->conn, &mtk_dsi_connector_helper_funcs);

	dsi->conn.dpms = DRM_MODE_DPMS_OFF;
	drm_connector_attach_encoder(&dsi->conn, &dsi->encoder);

	if (dsi->panel) {
		ret = drm_panel_attach(dsi->panel, &dsi->conn);
		if (ret) {
			DRM_ERROR("Failed to attach panel to drm\n");
			goto err_connector_cleanup;
		}
	}

	return 0;

err_connector_cleanup:
	drm_connector_cleanup(&dsi->conn);
	return ret;
}