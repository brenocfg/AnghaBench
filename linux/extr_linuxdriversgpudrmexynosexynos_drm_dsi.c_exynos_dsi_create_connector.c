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
struct drm_connector {int /*<<< orphan*/  status; int /*<<< orphan*/  polled; } ;
struct exynos_dsi {struct drm_connector connector; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_CONNECTOR_POLL_HPD ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DSI ; 
 int /*<<< orphan*/  connector_status_disconnected ; 
 int /*<<< orphan*/  drm_connector_attach_encoder (struct drm_connector*,struct drm_encoder*) ; 
 int /*<<< orphan*/  drm_connector_helper_add (struct drm_connector*,int /*<<< orphan*/ *) ; 
 int drm_connector_init (int /*<<< orphan*/ ,struct drm_connector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct exynos_dsi* encoder_to_dsi (struct drm_encoder*) ; 
 int /*<<< orphan*/  exynos_dsi_connector_funcs ; 
 int /*<<< orphan*/  exynos_dsi_connector_helper_funcs ; 

__attribute__((used)) static int exynos_dsi_create_connector(struct drm_encoder *encoder)
{
	struct exynos_dsi *dsi = encoder_to_dsi(encoder);
	struct drm_connector *connector = &dsi->connector;
	int ret;

	connector->polled = DRM_CONNECTOR_POLL_HPD;

	ret = drm_connector_init(encoder->dev, connector,
				 &exynos_dsi_connector_funcs,
				 DRM_MODE_CONNECTOR_DSI);
	if (ret) {
		DRM_ERROR("Failed to initialize connector with drm\n");
		return ret;
	}

	connector->status = connector_status_disconnected;
	drm_connector_helper_add(connector, &exynos_dsi_connector_helper_funcs);
	drm_connector_attach_encoder(connector, encoder);

	return 0;
}