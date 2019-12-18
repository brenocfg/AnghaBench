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
struct hdmi_platform_config {int pwr_clk_cnt; int pwr_reg_cnt; int /*<<< orphan*/ * pwr_reg_names; } ;
struct hdmi_bridge {struct hdmi* hdmi; } ;
struct hdmi {TYPE_1__* pdev; int /*<<< orphan*/ * pwr_regs; int /*<<< orphan*/ * pwr_clks; struct hdmi_platform_config* config; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_bridge {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 struct hdmi_bridge* to_hdmi_bridge (struct drm_bridge*) ; 

__attribute__((used)) static void power_off(struct drm_bridge *bridge)
{
	struct drm_device *dev = bridge->dev;
	struct hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	struct hdmi *hdmi = hdmi_bridge->hdmi;
	const struct hdmi_platform_config *config = hdmi->config;
	int i, ret;

	/* TODO do we need to wait for final vblank somewhere before
	 * cutting the clocks?
	 */
	mdelay(16 + 4);

	for (i = 0; i < config->pwr_clk_cnt; i++)
		clk_disable_unprepare(hdmi->pwr_clks[i]);

	for (i = 0; i < config->pwr_reg_cnt; i++) {
		ret = regulator_disable(hdmi->pwr_regs[i]);
		if (ret) {
			DRM_DEV_ERROR(dev->dev, "failed to disable pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
		}
	}

	pm_runtime_put_autosuspend(&hdmi->pdev->dev);
}