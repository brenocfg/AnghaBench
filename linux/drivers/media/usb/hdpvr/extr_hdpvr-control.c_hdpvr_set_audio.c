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
struct hdpvr_device {int flags; int* usbc_buf; int /*<<< orphan*/  usbc_mutex; int /*<<< orphan*/  udev; int /*<<< orphan*/  v4l2_dev; } ;
typedef  enum v4l2_mpeg_audio_encoding { ____Placeholder_v4l2_mpeg_audio_encoding } v4l2_mpeg_audio_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_AUDIO_INPUT_VALUE ; 
 int /*<<< orphan*/  CTRL_DEFAULT_INDEX ; 
 int EINVAL ; 
 int HDPVR_FLAG_AC3_CAP ; 
 int V4L2_MPEG_AUDIO_ENCODING_AAC ; 
 int V4L2_MPEG_AUDIO_ENCODING_AC3 ; 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

int hdpvr_set_audio(struct hdpvr_device *dev, u8 input,
		    enum v4l2_mpeg_audio_encoding codec)
{
	int ret = 0;

	if (dev->flags & HDPVR_FLAG_AC3_CAP) {
		mutex_lock(&dev->usbc_mutex);
		memset(dev->usbc_buf, 0, 2);
		dev->usbc_buf[0] = input;
		if (codec == V4L2_MPEG_AUDIO_ENCODING_AAC)
			dev->usbc_buf[1] = 0;
		else if (codec == V4L2_MPEG_AUDIO_ENCODING_AC3)
			dev->usbc_buf[1] = 1;
		else {
			mutex_unlock(&dev->usbc_mutex);
			v4l2_err(&dev->v4l2_dev, "invalid audio codec %d\n",
				 codec);
			ret = -EINVAL;
			goto error;
		}

		ret = usb_control_msg(dev->udev,
				      usb_sndctrlpipe(dev->udev, 0),
				      0x01, 0x38, CTRL_AUDIO_INPUT_VALUE,
				      CTRL_DEFAULT_INDEX, dev->usbc_buf, 2,
				      1000);
		mutex_unlock(&dev->usbc_mutex);
		if (ret == 2)
			ret = 0;
	} else
		ret = hdpvr_config_call(dev, CTRL_AUDIO_INPUT_VALUE, input);
error:
	return ret;
}