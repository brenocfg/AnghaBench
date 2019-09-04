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
struct TYPE_2__ {int /*<<< orphan*/  hdmi_dvi_mode; } ;
struct omap_hdmi {TYPE_1__ cfg; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_DVI ; 
 int /*<<< orphan*/  HDMI_HDMI ; 
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 

__attribute__((used)) static int hdmi_set_hdmi_mode(struct omap_dss_device *dssdev,
		bool hdmi_mode)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	hdmi->cfg.hdmi_dvi_mode = hdmi_mode ? HDMI_HDMI : HDMI_DVI;
	return 0;
}