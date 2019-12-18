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
struct sti_hdmi {int event_received; int /*<<< orphan*/  wait_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  HDMI_SRZ_CFG ; 
 int HDMI_SRZ_CFG_EN_BIASRES_DETECTION ; 
 int HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION ; 
 int /*<<< orphan*/  HDMI_SRZ_PLL_CFG ; 
 int /*<<< orphan*/  HDMI_STA ; 
 int HDMI_STA_DLL_LCK ; 
 int /*<<< orphan*/  HDMI_TIMEOUT_PLL_LOCK ; 
 int hdmi_read (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_hdmi_tx3g4c28phy_stop(struct sti_hdmi *hdmi)
{
	int val = 0;

	DRM_DEBUG_DRIVER("\n");

	hdmi->event_received = false;

	val = HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION;
	val |= HDMI_SRZ_CFG_EN_BIASRES_DETECTION;

	hdmi_write(hdmi, val, HDMI_SRZ_CFG);
	hdmi_write(hdmi, 0, HDMI_SRZ_PLL_CFG);

	/* wait PLL interrupt */
	wait_event_interruptible_timeout(hdmi->wait_event,
					 hdmi->event_received == true,
					 msecs_to_jiffies
					 (HDMI_TIMEOUT_PLL_LOCK));

	if (hdmi_read(hdmi, HDMI_STA) & HDMI_STA_DLL_LCK)
		DRM_ERROR("hdmi phy pll not well disabled\n");
}