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
struct omap_hdmi {int /*<<< orphan*/  pll; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  wp; int /*<<< orphan*/  pdev; struct dss_device* dss; } ;
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int) ; 
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct omap_hdmi*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int hdmi_audio_register (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_dump_regs ; 
 int hdmi_pll_init (struct dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_pll_uninit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi5_bind(struct device *dev, struct device *master, void *data)
{
	struct dss_device *dss = dss_get_device(master);
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);
	int r;

	hdmi->dss = dss;

	r = hdmi_pll_init(dss, hdmi->pdev, &hdmi->pll, &hdmi->wp);
	if (r)
		return r;

	r = hdmi_audio_register(hdmi);
	if (r) {
		DSSERR("Registering HDMI audio failed %d\n", r);
		goto err_pll_uninit;
	}

	hdmi->debugfs = dss_debugfs_create_file(dss, "hdmi", hdmi_dump_regs,
						hdmi);

	return 0;

err_pll_uninit:
	hdmi_pll_uninit(&hdmi->pll);
	return r;
}