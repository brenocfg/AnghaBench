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
struct hdmi_platform_config {int hpd_reg_cnt; int /*<<< orphan*/ * hpd_reg_names; } ;
struct hdmi_connector {struct hdmi* hdmi; } ;
struct hdmi {int /*<<< orphan*/ * hpd_regs; TYPE_1__* pdev; struct hdmi_platform_config* config; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_HDMI_HPD_INT_CTRL ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  enable_hpd_clocks (struct hdmi*,int) ; 
 int gpio_config (struct hdmi*,int) ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_hdmi_set_mode (struct hdmi*,int) ; 
 int pinctrl_pm_select_sleep_state (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdp_disable(struct hdmi_connector *hdmi_connector)
{
	struct hdmi *hdmi = hdmi_connector->hdmi;
	const struct hdmi_platform_config *config = hdmi->config;
	struct device *dev = &hdmi->pdev->dev;
	int i, ret = 0;

	/* Disable HPD interrupt */
	hdmi_write(hdmi, REG_HDMI_HPD_INT_CTRL, 0);

	msm_hdmi_set_mode(hdmi, false);

	enable_hpd_clocks(hdmi, false);
	pm_runtime_put_autosuspend(dev);

	ret = gpio_config(hdmi, false);
	if (ret)
		dev_warn(dev, "failed to unconfigure GPIOs: %d\n", ret);

	ret = pinctrl_pm_select_sleep_state(dev);
	if (ret)
		dev_warn(dev, "pinctrl state chg failed: %d\n", ret);

	for (i = 0; i < config->hpd_reg_cnt; i++) {
		ret = regulator_disable(hdmi->hpd_regs[i]);
		if (ret)
			dev_warn(dev, "failed to disable hpd regulator: %s (%d)\n",
					config->hpd_reg_names[i], ret);
	}
}