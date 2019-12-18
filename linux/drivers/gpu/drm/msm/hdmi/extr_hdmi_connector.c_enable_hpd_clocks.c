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
struct hdmi_platform_config {int hpd_clk_cnt; int /*<<< orphan*/ * hpd_clk_names; scalar_t__* hpd_freq; } ;
struct hdmi {int /*<<< orphan*/ * hpd_clks; TYPE_1__* pdev; struct hdmi_platform_config* config; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_hpd_clocks(struct hdmi *hdmi, bool enable)
{
	const struct hdmi_platform_config *config = hdmi->config;
	struct device *dev = &hdmi->pdev->dev;
	int i, ret;

	if (enable) {
		for (i = 0; i < config->hpd_clk_cnt; i++) {
			if (config->hpd_freq && config->hpd_freq[i]) {
				ret = clk_set_rate(hdmi->hpd_clks[i],
						   config->hpd_freq[i]);
				if (ret)
					dev_warn(dev,
						 "failed to set clk %s (%d)\n",
						 config->hpd_clk_names[i], ret);
			}

			ret = clk_prepare_enable(hdmi->hpd_clks[i]);
			if (ret) {
				DRM_DEV_ERROR(dev,
					"failed to enable hpd clk: %s (%d)\n",
					config->hpd_clk_names[i], ret);
			}
		}
	} else {
		for (i = config->hpd_clk_cnt - 1; i >= 0; i--)
			clk_disable_unprepare(hdmi->hpd_clks[i]);
	}
}