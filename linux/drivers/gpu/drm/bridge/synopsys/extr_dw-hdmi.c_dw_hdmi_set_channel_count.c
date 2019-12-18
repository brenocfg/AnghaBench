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
typedef  unsigned int u8 ;
struct dw_hdmi {int /*<<< orphan*/  audio_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_FC_AUDICONF0 ; 
 int /*<<< orphan*/  HDMI_FC_AUDICONF0_CC_MASK ; 
 unsigned int HDMI_FC_AUDICONF0_CC_OFFSET ; 
 int /*<<< orphan*/  HDMI_FC_AUDSCONF ; 
 unsigned int HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0 ; 
 unsigned int HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT1 ; 
 int /*<<< orphan*/  HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK ; 
 int /*<<< orphan*/  hdmi_modb (struct dw_hdmi*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void dw_hdmi_set_channel_count(struct dw_hdmi *hdmi, unsigned int cnt)
{
	u8 layout;

	mutex_lock(&hdmi->audio_mutex);

	/*
	 * For >2 channel PCM audio, we need to select layout 1
	 * and set an appropriate channel map.
	 */
	if (cnt > 2)
		layout = HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT1;
	else
		layout = HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_LAYOUT0;

	hdmi_modb(hdmi, layout, HDMI_FC_AUDSCONF_AUD_PACKET_LAYOUT_MASK,
		  HDMI_FC_AUDSCONF);

	/* Set the audio infoframes channel count */
	hdmi_modb(hdmi, (cnt - 1) << HDMI_FC_AUDICONF0_CC_OFFSET,
		  HDMI_FC_AUDICONF0_CC_MASK, HDMI_FC_AUDICONF0);

	mutex_unlock(&hdmi->audio_mutex);
}