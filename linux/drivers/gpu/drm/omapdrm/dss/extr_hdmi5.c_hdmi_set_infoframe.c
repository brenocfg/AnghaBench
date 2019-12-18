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
struct hdmi_avi_infoframe {int dummy; } ;
struct TYPE_2__ {struct hdmi_avi_infoframe infoframe; } ;
struct omap_hdmi {TYPE_1__ cfg; } ;
struct omap_dss_device {int dummy; } ;

/* Variables and functions */
 struct omap_hdmi* dssdev_to_hdmi (struct omap_dss_device*) ; 

__attribute__((used)) static int hdmi_set_infoframe(struct omap_dss_device *dssdev,
		const struct hdmi_avi_infoframe *avi)
{
	struct omap_hdmi *hdmi = dssdev_to_hdmi(dssdev);

	hdmi->cfg.infoframe = *avi;
	return 0;
}