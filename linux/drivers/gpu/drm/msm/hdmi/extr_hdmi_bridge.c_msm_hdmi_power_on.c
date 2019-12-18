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
struct hdmi_platform_config {int pwr_reg_cnt; int pwr_clk_cnt; int /*<<< orphan*/ * pwr_clk_names; int /*<<< orphan*/ * pwr_reg_names; } ;
struct hdmi_bridge {struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/ * pwr_clks; int /*<<< orphan*/  pixclock; int /*<<< orphan*/ * pwr_regs; TYPE_1__* pdev; struct hdmi_platform_config* config; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_bridge {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct hdmi_bridge* to_hdmi_bridge (struct drm_bridge*) ; 

__attribute__((used)) static void msm_hdmi_power_on(struct drm_bridge *bridge)
{
	struct drm_device *dev = bridge->dev;
	struct hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	struct hdmi *hdmi = hdmi_bridge->hdmi;
	const struct hdmi_platform_config *config = hdmi->config;
	int i, ret;

	pm_runtime_get_sync(&hdmi->pdev->dev);

	for (i = 0; i < config->pwr_reg_cnt; i++) {
		ret = regulator_enable(hdmi->pwr_regs[i]);
		if (ret) {
			DRM_DEV_ERROR(dev->dev, "failed to enable pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
		}
	}

	if (config->pwr_clk_cnt > 0) {
		DBG("pixclock: %lu", hdmi->pixclock);
		ret = clk_set_rate(hdmi->pwr_clks[0], hdmi->pixclock);
		if (ret) {
			DRM_DEV_ERROR(dev->dev, "failed to set pixel clk: %s (%d)\n",
					config->pwr_clk_names[0], ret);
		}
	}

	for (i = 0; i < config->pwr_clk_cnt; i++) {
		ret = clk_prepare_enable(hdmi->pwr_clks[i]);
		if (ret) {
			DRM_DEV_ERROR(dev->dev, "failed to enable pwr clk: %s (%d)\n",
					config->pwr_clk_names[i], ret);
		}
	}
}