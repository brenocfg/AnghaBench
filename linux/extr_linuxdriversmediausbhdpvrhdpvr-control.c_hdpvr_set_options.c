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
struct TYPE_2__ {scalar_t__ sharpness; scalar_t__ saturation; scalar_t__ hue; scalar_t__ contrast; scalar_t__ brightness; scalar_t__ gop_mode; scalar_t__ bitrate_mode; int /*<<< orphan*/  audio_codec; scalar_t__ audio_input; scalar_t__ video_input; scalar_t__ video_std; } ;
struct hdpvr_device {TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_BITRATE_MODE_VALUE ; 
 int /*<<< orphan*/  CTRL_BRIGHTNESS ; 
 int /*<<< orphan*/  CTRL_CONTRAST ; 
 int /*<<< orphan*/  CTRL_GOP_MODE_VALUE ; 
 int /*<<< orphan*/  CTRL_HUE ; 
 int /*<<< orphan*/  CTRL_SATURATION ; 
 int /*<<< orphan*/  CTRL_SHARPNESS ; 
 int /*<<< orphan*/  CTRL_VIDEO_INPUT_VALUE ; 
 int /*<<< orphan*/  CTRL_VIDEO_STD_TYPE ; 
 int /*<<< orphan*/  hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hdpvr_set_audio (struct hdpvr_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdpvr_set_bitrate (struct hdpvr_device*) ; 

int hdpvr_set_options(struct hdpvr_device *dev)
{
	hdpvr_config_call(dev, CTRL_VIDEO_STD_TYPE, dev->options.video_std);

	hdpvr_config_call(dev, CTRL_VIDEO_INPUT_VALUE,
			 dev->options.video_input+1);

	hdpvr_set_audio(dev, dev->options.audio_input+1,
		       dev->options.audio_codec);

	hdpvr_set_bitrate(dev);
	hdpvr_config_call(dev, CTRL_BITRATE_MODE_VALUE,
			 dev->options.bitrate_mode);
	hdpvr_config_call(dev, CTRL_GOP_MODE_VALUE, dev->options.gop_mode);

	hdpvr_config_call(dev, CTRL_BRIGHTNESS, dev->options.brightness);
	hdpvr_config_call(dev, CTRL_CONTRAST,   dev->options.contrast);
	hdpvr_config_call(dev, CTRL_HUE,        dev->options.hue);
	hdpvr_config_call(dev, CTRL_SATURATION, dev->options.saturation);
	hdpvr_config_call(dev, CTRL_SHARPNESS,  dev->options.sharpness);

	return 0;
}