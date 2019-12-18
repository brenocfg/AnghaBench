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
struct dw_mipi_dsi {struct dw_mipi_dsi* slave; } ;
struct drm_display_mode {int dummy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 struct dw_mipi_dsi* bridge_to_dsi (struct drm_bridge*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_mode_set (struct dw_mipi_dsi*,struct drm_display_mode const*) ; 

__attribute__((used)) static void dw_mipi_dsi_bridge_mode_set(struct drm_bridge *bridge,
					const struct drm_display_mode *mode,
					const struct drm_display_mode *adjusted_mode)
{
	struct dw_mipi_dsi *dsi = bridge_to_dsi(bridge);

	dw_mipi_dsi_mode_set(dsi, adjusted_mode);
	if (dsi->slave)
		dw_mipi_dsi_mode_set(dsi->slave, adjusted_mode);
}