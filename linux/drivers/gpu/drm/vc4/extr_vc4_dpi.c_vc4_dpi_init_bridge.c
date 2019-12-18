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
struct vc4_dpi {int /*<<< orphan*/  encoder; TYPE_1__* pdev; } ;
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DPI ; 
 int ENODEV ; 
 int drm_bridge_attach (int /*<<< orphan*/ ,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_panel**,struct drm_bridge**) ; 
 struct drm_bridge* drm_panel_bridge_add (struct drm_panel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_dpi_init_bridge(struct vc4_dpi *dpi)
{
	struct device *dev = &dpi->pdev->dev;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	int ret;

	ret = drm_of_find_panel_or_bridge(dev->of_node, 0, 0,
					  &panel, &bridge);
	if (ret) {
		/* If nothing was connected in the DT, that's not an
		 * error.
		 */
		if (ret == -ENODEV)
			return 0;
		else
			return ret;
	}

	if (panel)
		bridge = drm_panel_bridge_add(panel, DRM_MODE_CONNECTOR_DPI);

	return drm_bridge_attach(dpi->encoder, bridge, NULL);
}