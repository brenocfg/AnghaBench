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
struct dw_mipi_dsi {int /*<<< orphan*/  panel_bridge; } ;
struct drm_bridge {TYPE_1__* encoder; } ;
struct TYPE_2__ {int /*<<< orphan*/  encoder_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  DRM_MODE_ENCODER_DSI ; 
 int ENODEV ; 
 struct dw_mipi_dsi* bridge_to_dsi (struct drm_bridge*) ; 
 int drm_bridge_attach (TYPE_1__*,int /*<<< orphan*/ ,struct drm_bridge*) ; 

__attribute__((used)) static int dw_mipi_dsi_bridge_attach(struct drm_bridge *bridge)
{
	struct dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	if (!bridge->encoder) {
		DRM_ERROR("Parent encoder object not found\n");
		return -ENODEV;
	}

	/* Set the encoder type as caller does not know it */
	bridge->encoder->encoder_type = DRM_MODE_ENCODER_DSI;

	/* Attach the panel-bridge to the dsi bridge */
	return drm_bridge_attach(bridge->encoder, dsi->panel_bridge, bridge);
}