#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_dss_device {int dummy; } ;
struct hdmi_avi_infoframe {int dummy; } ;
struct TYPE_3__ {struct hdmi_avi_infoframe infoframe; } ;
struct TYPE_4__ {TYPE_1__ cfg; } ;

/* Variables and functions */
 TYPE_2__ hdmi ; 

__attribute__((used)) static int hdmi_set_infoframe(struct omap_dss_device *dssdev,
		const struct hdmi_avi_infoframe *avi)
{
	hdmi.cfg.infoframe = *avi;
	return 0;
}