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
struct omap_hdmi {int /*<<< orphan*/  output; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int dss_mgr_connect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 
 int hdmi_init_regulator (struct omap_hdmi*) ; 
 int omapdss_output_set_device (struct omap_dss_device*,struct omap_dss_device*) ; 

__attribute__((used)) static int hdmi_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);
	int r;

	r = hdmi_init_regulator(hdmi);
	if (r)
		return r;

	r = dss_mgr_connect(&hdmi->output, dssdev);
	if (r)
		return r;

	r = omapdss_output_set_device(dssdev, dst);
	if (r) {
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(&hdmi->output, dssdev);
		return r;
	}

	return 0;
}