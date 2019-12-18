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
struct TYPE_3__ {unsigned int sample_rate; } ;
struct TYPE_4__ {scalar_t__ aud_input_type; int /*<<< orphan*/  aud_mclk; TYPE_1__ codec_params; } ;
struct mtk_hdmi {TYPE_2__ aud_param; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG2_ACLK_INV ; 
 int EINVAL ; 
 int /*<<< orphan*/  GRL_CFG2 ; 
 scalar_t__ HDMI_AUD_INPUT_I2S ; 
 int /*<<< orphan*/  HDMI_AUD_MCLK_128FS ; 
 int /*<<< orphan*/  mtk_hdmi_aud_on_off_hw_ncts (struct mtk_hdmi*,int) ; 
 int /*<<< orphan*/  mtk_hdmi_clear_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_mclk (struct mtk_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_set_ncts (struct mtk_hdmi*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_src_disable (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_aud_src_reenable (struct mtk_hdmi*) ; 

__attribute__((used)) static int mtk_hdmi_aud_set_src(struct mtk_hdmi *hdmi,
				struct drm_display_mode *display_mode)
{
	unsigned int sample_rate = hdmi->aud_param.codec_params.sample_rate;

	mtk_hdmi_aud_on_off_hw_ncts(hdmi, false);
	mtk_hdmi_hw_aud_src_disable(hdmi);
	mtk_hdmi_clear_bits(hdmi, GRL_CFG2, CFG2_ACLK_INV);

	if (hdmi->aud_param.aud_input_type == HDMI_AUD_INPUT_I2S) {
		switch (sample_rate) {
		case 32000:
		case 44100:
		case 48000:
		case 88200:
		case 96000:
			break;
		default:
			return -EINVAL;
		}
		mtk_hdmi_hw_aud_set_mclk(hdmi, hdmi->aud_param.aud_mclk);
	} else {
		switch (sample_rate) {
		case 32000:
		case 44100:
		case 48000:
			break;
		default:
			return -EINVAL;
		}
		mtk_hdmi_hw_aud_set_mclk(hdmi, HDMI_AUD_MCLK_128FS);
	}

	mtk_hdmi_hw_aud_set_ncts(hdmi, sample_rate, display_mode->clock);

	mtk_hdmi_hw_aud_src_reenable(hdmi);
	return 0;
}