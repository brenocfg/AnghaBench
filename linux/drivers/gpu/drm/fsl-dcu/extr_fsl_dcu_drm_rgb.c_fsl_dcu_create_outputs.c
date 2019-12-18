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
struct TYPE_2__ {struct drm_panel* panel; } ;
struct fsl_dcu_drm_device {int /*<<< orphan*/  encoder; TYPE_1__ connector; int /*<<< orphan*/  np; } ;
struct drm_panel {int dummy; } ;
struct drm_bridge {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_panel*) ; 
 int PTR_ERR (struct drm_panel*) ; 
 int drm_bridge_attach (int /*<<< orphan*/ *,struct drm_bridge*,int /*<<< orphan*/ *) ; 
 int drm_of_find_panel_or_bridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_panel**,struct drm_bridge**) ; 
 int fsl_dcu_attach_panel (struct fsl_dcu_drm_device*,struct drm_panel*) ; 
 struct drm_panel* of_drm_find_panel (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fsl_dcu_create_outputs(struct fsl_dcu_drm_device *fsl_dev)
{
	struct device_node *panel_node;
	struct drm_panel *panel;
	struct drm_bridge *bridge;
	int ret;

	/* This is for backward compatibility */
	panel_node = of_parse_phandle(fsl_dev->np, "fsl,panel", 0);
	if (panel_node) {
		fsl_dev->connector.panel = of_drm_find_panel(panel_node);
		of_node_put(panel_node);
		if (IS_ERR(fsl_dev->connector.panel))
			return PTR_ERR(fsl_dev->connector.panel);

		return fsl_dcu_attach_panel(fsl_dev, fsl_dev->connector.panel);
	}

	ret = drm_of_find_panel_or_bridge(fsl_dev->np, 0, 0, &panel, &bridge);
	if (ret)
		return ret;

	if (panel) {
		fsl_dev->connector.panel = panel;
		return fsl_dcu_attach_panel(fsl_dev, panel);
	}

	return drm_bridge_attach(&fsl_dev->encoder, bridge, NULL);
}