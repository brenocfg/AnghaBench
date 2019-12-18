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
struct mtk_hdmi {int /*<<< orphan*/  mode; int /*<<< orphan*/  aud_param; int /*<<< orphan*/  dev; int /*<<< orphan*/  audio_enable; } ;
struct TYPE_2__ {int /*<<< orphan*/  sample_rate; } ;
struct hdmi_audio_param {TYPE_1__ codec_params; int /*<<< orphan*/  aud_input_chan_type; int /*<<< orphan*/  aud_input_type; int /*<<< orphan*/  aud_codec; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hdmi_audio_param*,int) ; 
 int mtk_hdmi_aud_output_config (struct mtk_hdmi*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_hdmi_audio_set_param(struct mtk_hdmi *hdmi,
				    struct hdmi_audio_param *param)
{
	if (!hdmi->audio_enable) {
		dev_err(hdmi->dev, "hdmi audio is in disable state!\n");
		return -EINVAL;
	}
	dev_dbg(hdmi->dev, "codec:%d, input:%d, channel:%d, fs:%d\n",
		param->aud_codec, param->aud_input_type,
		param->aud_input_chan_type, param->codec_params.sample_rate);
	memcpy(&hdmi->aud_param, param, sizeof(*param));
	return mtk_hdmi_aud_output_config(hdmi, &hdmi->mode);
}