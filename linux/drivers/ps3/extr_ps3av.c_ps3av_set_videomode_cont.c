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
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS3AV_CMD_AV_HDMI_HDCP_OFF ; 
 int /*<<< orphan*/  PS3AV_CMD_AV_HDMI_MODE_NORMAL ; 
 int /*<<< orphan*/  PS3AV_CMD_MUTE_OFF ; 
 int PS3AV_MODE_480P ; 
 int PS3AV_MODE_HDCP_OFF ; 
 int PS3AV_MODE_MASK ; 
 int PS3AV_MODE_WXGA ; 
 int PS3AV_STATUS_UNSUPPORTED_HDMI_MODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 TYPE_2__* ps3av ; 
 int ps3av_cmd_av_hdmi_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_set_av_video_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps3av_set_video_disable_sig () ; 
 int /*<<< orphan*/  ps3av_set_videomode_packet (int) ; 

__attribute__((used)) static void ps3av_set_videomode_cont(u32 id, u32 old_id)
{
	static int vesa;
	int res;

	/* video signal off */
	ps3av_set_video_disable_sig();

	/*
	 * AV backend needs non-VESA mode setting at least one time
	 * when VESA mode is used.
	 */
	if (vesa == 0 && (id & PS3AV_MODE_MASK) >= PS3AV_MODE_WXGA) {
		/* vesa mode */
		ps3av_set_videomode_packet(PS3AV_MODE_480P);
	}
	vesa = 1;

	/* Retail PS3 product doesn't support this */
	if (id & PS3AV_MODE_HDCP_OFF) {
		res = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_HDCP_OFF);
		if (res == PS3AV_STATUS_UNSUPPORTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->core, "Not supported\n");
		else if (res)
			dev_dbg(&ps3av->dev->core,
				"ps3av_cmd_av_hdmi_mode failed\n");
	} else if (old_id & PS3AV_MODE_HDCP_OFF) {
		res = ps3av_cmd_av_hdmi_mode(PS3AV_CMD_AV_HDMI_MODE_NORMAL);
		if (res < 0 && res != PS3AV_STATUS_UNSUPPORTED_HDMI_MODE)
			dev_dbg(&ps3av->dev->core,
				"ps3av_cmd_av_hdmi_mode failed\n");
	}

	ps3av_set_videomode_packet(id);

	msleep(1500);
	/* av video mute */
	ps3av_set_av_video_mute(PS3AV_CMD_MUTE_OFF);
}