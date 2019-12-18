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
struct omap_hdmi {int /*<<< orphan*/  pll; int /*<<< orphan*/  core; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  wp; int /*<<< orphan*/  pdev; struct dss_device* dss; } ;
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct omap_hdmi*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int hdmi4_cec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi4_cec_uninit (int /*<<< orphan*/ *) ; 
 int hdmi_audio_register (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_dump_regs ; 
 int hdmi_pll_init (struct dss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi_pll_uninit (int /*<<< orphan*/ *) ; 
 int hdmi_runtime_get (struct omap_hdmi*) ; 
 int /*<<< orphan*/  hdmi_runtime_put (struct omap_hdmi*) ; 

__attribute__((used)) static int hdmi4_bind(struct device *dev, struct device *master, void *data)
{
	struct dss_device *dss = dss_get_device(master);
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);
	int r;

	hdmi->dss = dss;

	r = hdmi_runtime_get(hdmi);
	if (r)
		return r;

	r = hdmi_pll_init(dss, hdmi->pdev, &hdmi->pll, &hdmi->wp);
	if (r)
		goto err_runtime_put;

	r = hdmi4_cec_init(hdmi->pdev, &hdmi->core, &hdmi->wp);
	if (r)
		goto err_pll_uninit;

	r = hdmi_audio_register(hdmi);
	if (r) {
		DSSERR("Registering HDMI audio failed\n");
		goto err_cec_uninit;
	}

	hdmi->debugfs = dss_debugfs_create_file(dss, "hdmi", hdmi_dump_regs,
					       hdmi);

	hdmi_runtime_put(hdmi);

	return 0;

err_cec_uninit:
	hdmi4_cec_uninit(&hdmi->core);
err_pll_uninit:
	hdmi_pll_uninit(&hdmi->pll);
err_runtime_put:
	hdmi_runtime_put(hdmi);
	return r;
}