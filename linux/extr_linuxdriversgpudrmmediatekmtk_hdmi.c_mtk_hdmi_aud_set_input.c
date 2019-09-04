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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ aud_input_type; scalar_t__ aud_codec; scalar_t__ aud_i2s_fmt; int aud_input_chan_type; } ;
struct mtk_hdmi {TYPE_1__ aud_param; } ;
typedef  enum hdmi_aud_channel_type { ____Placeholder_hdmi_aud_channel_type } hdmi_aud_channel_type ;

/* Variables and functions */
 int /*<<< orphan*/  GRL_MIX_CTRL ; 
 scalar_t__ HDMI_AUDIO_CODING_TYPE_DST ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_SIZE_24 ; 
 int HDMI_AUD_CHAN_TYPE_2_0 ; 
 scalar_t__ HDMI_AUD_INPUT_SPDIF ; 
 int /*<<< orphan*/  HDMI_AUD_SWAP_LFE_CC ; 
 scalar_t__ HDMI_I2S_MODE_LJT_16BIT ; 
 scalar_t__ HDMI_I2S_MODE_LJT_24BIT ; 
 int /*<<< orphan*/  MIX_CTRL_FLAT ; 
 int /*<<< orphan*/  mtk_hdmi_aud_get_chnl_count (int) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_bit_num (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_channel_swap (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_i2s_chan_num (struct mtk_hdmi*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_i2s_fmt (struct mtk_hdmi*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_input_type (struct mtk_hdmi*,scalar_t__) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_audio_config (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_set_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hdmi_aud_set_input(struct mtk_hdmi *hdmi)
{
	enum hdmi_aud_channel_type chan_type;
	u8 chan_count;
	bool dst;

	mtk_hdmi_hw_aud_set_channel_swap(hdmi, HDMI_AUD_SWAP_LFE_CC);
	mtk_hdmi_set_bits(hdmi, GRL_MIX_CTRL, MIX_CTRL_FLAT);

	if (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF &&
	    hdmi->aud_param.aud_codec == HDMI_AUDIO_CODING_TYPE_DST) {
		mtk_hdmi_hw_aud_set_bit_num(hdmi, HDMI_AUDIO_SAMPLE_SIZE_24);
	} else if (hdmi->aud_param.aud_i2s_fmt == HDMI_I2S_MODE_LJT_24BIT) {
		hdmi->aud_param.aud_i2s_fmt = HDMI_I2S_MODE_LJT_16BIT;
	}

	mtk_hdmi_hw_aud_set_i2s_fmt(hdmi, hdmi->aud_param.aud_i2s_fmt);
	mtk_hdmi_hw_aud_set_bit_num(hdmi, HDMI_AUDIO_SAMPLE_SIZE_24);

	dst = ((hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF) &&
	       (hdmi->aud_param.aud_codec == HDMI_AUDIO_CODING_TYPE_DST));
	mtk_hdmi_hw_audio_config(hdmi, dst);

	if (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_SPDIF)
		chan_type = HDMI_AUD_CHAN_TYPE_2_0;
	else
		chan_type = hdmi->aud_param.aud_input_chan_type;
	chan_count = mtk_hdmi_aud_get_chnl_count(chan_type);
	mtk_hdmi_hw_aud_set_i2s_chan_num(hdmi, chan_type, chan_count);
	mtk_hdmi_hw_aud_set_input_type(hdmi, hdmi->aud_param.aud_input_type);

	return 0;
}