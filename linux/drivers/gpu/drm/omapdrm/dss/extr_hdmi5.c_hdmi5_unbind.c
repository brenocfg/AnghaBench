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
struct omap_hdmi {int /*<<< orphan*/  pll; scalar_t__ audio_pdev; int /*<<< orphan*/  debugfs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct omap_hdmi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_pll_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static void hdmi5_unbind(struct device *dev, struct device *master, void *data)
{
	struct omap_hdmi *hdmi = dev_get_drvdata(dev);

	dss_debugfs_remove_file(hdmi->debugfs);

	if (hdmi->audio_pdev)
		platform_device_unregister(hdmi->audio_pdev);

	hdmi_pll_uninit(&hdmi->pll);
}