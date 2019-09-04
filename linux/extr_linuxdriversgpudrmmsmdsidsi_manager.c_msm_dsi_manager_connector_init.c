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
typedef  int /*<<< orphan*/  u8 ;
struct msm_dsi {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;
struct drm_connector {scalar_t__ doublescan_allowed; scalar_t__ interlace_allowed; int /*<<< orphan*/  polled; } ;
struct dsi_connector {struct drm_connector base; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int ENOMEM ; 
 struct drm_connector* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_mgr_conn_helper_funcs ; 
 int /*<<< orphan*/  dsi_mgr_connector_funcs ; 
 struct msm_dsi* dsi_mgr_get_dsi (int /*<<< orphan*/ ) ; 
 struct dsi_connector* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_connector *msm_dsi_manager_connector_init(u8 id)
{
	struct msm_dsi *msm_dsi = dsi_mgr_get_dsi(id);
	struct drm_connector *connector = NULL;
	struct dsi_connector *dsi_connector;
	int ret;

	dsi_connector = kzalloc(sizeof(*dsi_connector), GFP_KERNEL);
	if (!dsi_connector)
		return ERR_PTR(-ENOMEM);

	dsi_connector->id = id;

	connector = &dsi_connector->base;

	ret = drm_connector_init(msm_dsi->dev, connector,
			&dsi_mgr_connector_funcs, DRM_MODE_CONNECTOR_DSI);
	if (ret)
		return ERR_PTR(ret);

	drm_connector_helper_add(connector, &dsi_mgr_conn_helper_funcs);

	/* Enable HPD to let hpd event is handled
	 * when panel is attached to the host.
	 */
	connector->polled = DRM_CONNECTOR_POLL_HPD;

	/* Display driver doesn't support interlace now. */
	connector->interlace_allowed = 0;
	connector->doublescan_allowed = 0;

	drm_connector_attach_encoder(connector, msm_dsi->encoder);

	return connector;
}