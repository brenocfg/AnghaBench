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
struct TYPE_4__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_size; int /*<<< orphan*/  sample_frequency; int /*<<< orphan*/  coding_type; } ;
union hdmi_infoframe {TYPE_2__ audio; } ;
struct TYPE_3__ {int /*<<< orphan*/  channels; } ;
struct vc4_hdmi {TYPE_1__ audio; } ;
struct vc4_dev {struct vc4_hdmi* hdmi; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct vc4_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_AUDIO_CODING_TYPE_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM ; 
 int /*<<< orphan*/  HDMI_AUDIO_SAMPLE_SIZE_STREAM ; 
 int hdmi_audio_infoframe_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vc4_hdmi_write_infoframe (struct drm_encoder*,union hdmi_infoframe*) ; 

__attribute__((used)) static void vc4_hdmi_set_audio_infoframe(struct drm_encoder *encoder)
{
	struct drm_device *drm = encoder->dev;
	struct vc4_dev *vc4 = drm->dev_private;
	struct vc4_hdmi *hdmi = vc4->hdmi;
	union hdmi_infoframe frame;
	int ret;

	ret = hdmi_audio_infoframe_init(&frame.audio);

	frame.audio.coding_type = HDMI_AUDIO_CODING_TYPE_STREAM;
	frame.audio.sample_frequency = HDMI_AUDIO_SAMPLE_FREQUENCY_STREAM;
	frame.audio.sample_size = HDMI_AUDIO_SAMPLE_SIZE_STREAM;
	frame.audio.channels = hdmi->audio.channels;

	vc4_hdmi_write_infoframe(encoder, &frame);
}