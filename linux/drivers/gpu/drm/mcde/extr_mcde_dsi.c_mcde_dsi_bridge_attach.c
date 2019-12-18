#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  polled; } ;
struct mcde_dsi {TYPE_1__ connector; int /*<<< orphan*/  dev; int /*<<< orphan*/  bridge_out; } ;
struct drm_device {int dummy; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_ATOMIC ; 
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_CONNECT ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int ENOTSUPP ; 
 struct mcde_dsi* bridge_to_mcde_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  connector_status_connected ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int drm_bridge_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (struct drm_device*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_dsi_connector_funcs ; 
 int /*<<< orphan*/  mcde_dsi_connector_helper_funcs ; 

__attribute__((used)) static int mcde_dsi_bridge_attach(struct drm_bridge *bridge)
{
	struct mcde_dsi *d = bridge_to_mcde_dsi(bridge);
	struct drm_device *drm = bridge->dev;
	int ret;

	drm_connector_helper_add(&d->connector,
				 &mcde_dsi_connector_helper_funcs);

	if (!drm_core_check_feature(drm, DRIVER_ATOMIC)) {
		dev_err(d->dev, "we need atomic updates\n");
		return -ENOTSUPP;
	}

	ret = drm_connector_init(drm, &d->connector,
				 &mcde_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	if (ret) {
		dev_err(d->dev, "failed to initialize DSI bridge connector\n");
		return ret;
	}
	d->connector.polled = DRM_CONNECTOR_POLL_CONNECT;
	/* The encoder in the bridge attached to the DSI bridge */
	drm_connector_attach_encoder(&d->connector, bridge->encoder);
	/* Then we attach the DSI bridge to the output (panel etc) bridge */
	ret = drm_bridge_attach(bridge->encoder, d->bridge_out, bridge);
	if (ret) {
		dev_err(d->dev, "failed to attach the DSI bridge\n");
		return ret;
	}
	d->connector.status = connector_status_connected;

	return 0;
}