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
typedef  int u32 ;
struct sti_hdmi {int event_received; int /*<<< orphan*/  clk_audio; int /*<<< orphan*/  wait_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  HDMI_CFG ; 
 int HDMI_CFG_SW_RST_EN ; 
 int /*<<< orphan*/  HDMI_STA ; 
 int HDMI_STA_SW_RST ; 
 int /*<<< orphan*/  HDMI_TIMEOUT_SWRESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int hdmi_read (struct sti_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_swreset(struct sti_hdmi *hdmi)
{
	u32 val;

	DRM_DEBUG_DRIVER("\n");

	/* Enable hdmi_audio clock only during hdmi reset */
	if (clk_prepare_enable(hdmi->clk_audio))
		DRM_INFO("Failed to prepare/enable hdmi_audio clk\n");

	/* Sw reset */
	hdmi->event_received = false;

	val = hdmi_read(hdmi, HDMI_CFG);
	val |= HDMI_CFG_SW_RST_EN;
	hdmi_write(hdmi, val, HDMI_CFG);

	/* Wait reset completed */
	wait_event_interruptible_timeout(hdmi->wait_event,
					 hdmi->event_received,
					 msecs_to_jiffies
					 (HDMI_TIMEOUT_SWRESET));

	/*
	 * HDMI_STA_SW_RST bit is set to '1' when SW_RST bit in HDMI_CFG is
	 * set to '1' and clk_audio is running.
	 */
	if ((hdmi_read(hdmi, HDMI_STA) & HDMI_STA_SW_RST) == 0)
		DRM_DEBUG_DRIVER("Warning: HDMI sw reset timeout occurs\n");

	val = hdmi_read(hdmi, HDMI_CFG);
	val &= ~HDMI_CFG_SW_RST_EN;
	hdmi_write(hdmi, val, HDMI_CFG);

	/* Disable hdmi_audio clock. Not used anymore for drm purpose */
	clk_disable_unprepare(hdmi->clk_audio);
}