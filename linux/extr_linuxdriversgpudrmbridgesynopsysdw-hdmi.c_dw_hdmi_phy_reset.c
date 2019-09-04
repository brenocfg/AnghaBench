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

/* Variables and functions */
 int /*<<< orphan*/  HDMI_MC_PHYRSTZ ; 
 int /*<<< orphan*/  HDMI_MC_PHYRSTZ_PHYRSTZ ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dw_hdmi_phy_reset(struct dw_hdmi *hdmi)
{
	/* PHY reset. The reset signal is active high on Gen2 PHYs. */
	hdmi_writeb(hdmi, HDMI_MC_PHYRSTZ_PHYRSTZ, HDMI_MC_PHYRSTZ);
	hdmi_writeb(hdmi, 0, HDMI_MC_PHYRSTZ);
}