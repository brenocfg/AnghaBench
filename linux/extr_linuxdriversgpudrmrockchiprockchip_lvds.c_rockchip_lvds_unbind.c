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
struct rockchip_lvds {int /*<<< orphan*/  encoder; int /*<<< orphan*/  connector; scalar_t__ panel; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct rockchip_lvds* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_connector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_encoder_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_panel_detach (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  rockchip_lvds_encoder_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rockchip_lvds_unbind(struct device *dev, struct device *master,
				void *data)
{
	struct rockchip_lvds *lvds = dev_get_drvdata(dev);

	rockchip_lvds_encoder_disable(&lvds->encoder);
	if (lvds->panel)
		drm_panel_detach(lvds->panel);
	pm_runtime_disable(dev);
	drm_connector_cleanup(&lvds->connector);
	drm_encoder_cleanup(&lvds->encoder);
}