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
struct TYPE_2__ {int /*<<< orphan*/  aud_input_chan_type; } ;
struct mtk_hdmi {int /*<<< orphan*/  dev; TYPE_1__ aud_param; } ;
struct hdmi_audio_infoframe {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_frequency; int /*<<< orphan*/  coding_type; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUDIO_CODING_TYPE_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_SIZE_STREAM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ hdmi_audio_infoframe_init (struct hdmi_audio_infoframe*) ; 
 scalar_t__ hdmi_audio_infoframe_pack (struct hdmi_audio_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtk_hdmi_aud_get_chnl_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_send_info_frame (struct mtk_hdmi*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mtk_hdmi_setup_audio_infoframe(struct mtk_hdmi *hdmi)
{
	struct hdmi_audio_infoframe frame;
	u8 buffer[14];
	ssize_t err;

	err = hdmi_audio_infoframe_init(&frame);
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to setup audio infoframe: %zd\n",
			err);
		return err;
	}

	frame.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	frame.sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	frame.sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	frame.channels = mtk_hdmi_aud_get_chnl_count(
					hdmi->aud_param.aud_input_chan_type);

	err = hdmi_audio_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to pack audio infoframe: %zd\n",
			err);
		return err;
	}

	mtk_hdmi_hw_send_info_frame(hdmi, buffer, sizeof(buffer));
	return 0;
}