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
struct dw_hdmi {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_phy_sel_data_en_pol (struct dw_hdmi*,int) ; 
 int /*<<< orphan*/  dw_hdmi_phy_sel_interface_control (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int hdmi_phy_configure (struct dw_hdmi*) ; 

__attribute__((used)) static int dw_hdmi_phy_init(struct dw_hdmi *hdmi, void *data,
			    struct drm_display_mode *mode)
{
	int i, ret;

	/* HDMI Phy spec says to do the phy initialization sequence twice */
	for (i = 0; i < 2; i++) {
		dw_hdmi_phy_sel_data_en_pol(hdmi, 1);
		dw_hdmi_phy_sel_interface_control(hdmi, 0);

		ret = hdmi_phy_configure(hdmi);
		if (ret)
			return ret;
	}

	return 0;
}