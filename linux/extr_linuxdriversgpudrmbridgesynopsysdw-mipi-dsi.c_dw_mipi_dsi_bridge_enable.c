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
struct dw_mipi_dsi {int dummy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPI_DSI_MODE_VIDEO ; 
 struct dw_mipi_dsi* bridge_to_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_set_mode (struct dw_mipi_dsi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mipi_dsi_bridge_enable(struct drm_bridge *bridge)
{
	struct dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	/* Switch to video mode for panel-bridge enable & panel enable */
	dw_mipi_dsi_set_mode(dsi, MIPI_DSI_MODE_VIDEO);
}