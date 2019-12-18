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
typedef  int u8 ;
struct mtk_hdmi {int dummy; } ;
typedef  enum hdmi_aud_channel_type { ____Placeholder_hdmi_aud_channel_type } hdmi_aud_channel_type ;

/* Variables and functions */
 unsigned int CH_SWITCH (int,int) ; 
 int /*<<< orphan*/  GRL_CH_SW0 ; 
 int /*<<< orphan*/  GRL_CH_SW1 ; 
 int /*<<< orphan*/  GRL_CH_SW2 ; 
 int /*<<< orphan*/  GRL_I2S_UV ; 
 int HDMI_AUD_CHAN_TYPE_3_0_LRS ; 
 int HDMI_AUD_CHAN_TYPE_4_0 ; 
 int HDMI_AUD_CHAN_TYPE_4_1_CLRS ; 
 int HDMI_AUD_CHAN_TYPE_5_1 ; 
 int I2S_UV_CH_EN (int) ; 
 int /*<<< orphan*/  mtk_hdmi_write (struct mtk_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_set_i2s_chan_num(struct mtk_hdmi *hdmi,
					enum hdmi_aud_channel_type channel_type,
					u8 channel_count)
{
	unsigned int ch_switch;
	u8 i2s_uv;

	ch_switch = CH_SWITCH(7, 7) | CH_SWITCH(6, 6) |
		    CH_SWITCH(5, 5) | CH_SWITCH(4, 4) |
		    CH_SWITCH(3, 3) | CH_SWITCH(1, 2) |
		    CH_SWITCH(2, 1) | CH_SWITCH(0, 0);

	if (channel_count == 2) {
		i2s_uv = I2S_UV_CH_EN(0);
	} else if (channel_count == 3 || channel_count == 4) {
		if (channel_count == 4 &&
		    (channel_type == HDMI_AUD_CHAN_TYPE_3_0_LRS ||
		    channel_type == HDMI_AUD_CHAN_TYPE_4_0))
			i2s_uv = I2S_UV_CH_EN(2) | I2S_UV_CH_EN(0);
		else
			i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2);
	} else if (channel_count == 6 || channel_count == 5) {
		if (channel_count == 6 &&
		    channel_type != HDMI_AUD_CHAN_TYPE_5_1 &&
		    channel_type != HDMI_AUD_CHAN_TYPE_4_1_CLRS) {
			i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2) |
				 I2S_UV_CH_EN(1) | I2S_UV_CH_EN(0);
		} else {
			i2s_uv = I2S_UV_CH_EN(2) | I2S_UV_CH_EN(1) |
				 I2S_UV_CH_EN(0);
		}
	} else if (channel_count == 8 || channel_count == 7) {
		i2s_uv = I2S_UV_CH_EN(3) | I2S_UV_CH_EN(2) |
			 I2S_UV_CH_EN(1) | I2S_UV_CH_EN(0);
	} else {
		i2s_uv = I2S_UV_CH_EN(0);
	}

	mtk_hdmi_write(hdmi, GRL_CH_SW0, ch_switch & 0xff);
	mtk_hdmi_write(hdmi, GRL_CH_SW1, (ch_switch >> 8) & 0xff);
	mtk_hdmi_write(hdmi, GRL_CH_SW2, (ch_switch >> 16) & 0xff);
	mtk_hdmi_write(hdmi, GRL_I2S_UV, i2s_uv);
}