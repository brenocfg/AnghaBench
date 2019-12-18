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
struct s6d16d0 {int /*<<< orphan*/  dev; } ;
struct mipi_dsi_device {int dummy; } ;
struct drm_panel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int mipi_dsi_dcs_set_display_on (struct mipi_dsi_device*) ; 
 struct s6d16d0* panel_to_s6d16d0 (struct drm_panel*) ; 
 struct mipi_dsi_device* to_mipi_dsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6d16d0_enable(struct drm_panel *panel)
{
	struct s6d16d0 *s6 = panel_to_s6d16d0(panel);
	struct mipi_dsi_device *dsi = to_mipi_dsi_device(s6->dev);
	int ret;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret) {
		DRM_DEV_ERROR(s6->dev, "failed to turn display on (%d)\n",
			      ret);
		return ret;
	}

	return 0;
}