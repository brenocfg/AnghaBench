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
struct TYPE_6__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  polled; } ;
struct ptn3460_bridge {TYPE_1__ connector; scalar_t__ panel; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_LVDS ; 
 int ENODEV ; 
 struct ptn3460_bridge* bridge_to_ptn3460 (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_helper_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_connector_register (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_attach (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ptn3460_connector_funcs ; 
 int /*<<< orphan*/  ptn3460_connector_helper_funcs ; 

__attribute__((used)) static int ptn3460_bridge_attach(struct drm_bridge *bridge)
{
	struct ptn3460_bridge *ptn_bridge = bridge_to_ptn3460(bridge);
	int ret;

	if (!bridge->encoder) {
		DRM_ERROR("Parent encoder object not found");
		return -ENODEV;
	}

	ptn_bridge->connector.polled = DRM_CONNECTOR_POLL_HPD;
	ret = drm_connector_init(bridge->dev, &ptn_bridge->connector,
			&ptn3460_connector_funcs, DRM_MODE_CONNECTOR_LVDS);
	if (ret) {
		DRM_ERROR("Failed to initialize connector with drm\n");
		return ret;
	}
	drm_connector_helper_add(&ptn_bridge->connector,
					&ptn3460_connector_helper_funcs);
	drm_connector_register(&ptn_bridge->connector);
	drm_connector_attach_encoder(&ptn_bridge->connector,
							bridge->encoder);

	if (ptn_bridge->panel)
		drm_panel_attach(ptn_bridge->panel, &ptn_bridge->connector);

	drm_helper_hpd_irq_event(ptn_bridge->connector.dev);

	return ret;
}