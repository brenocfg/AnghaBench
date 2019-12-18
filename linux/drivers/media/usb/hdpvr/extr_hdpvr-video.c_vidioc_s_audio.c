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
struct v4l2_audio {scalar_t__ index; } ;
struct TYPE_2__ {scalar_t__ audio_input; int /*<<< orphan*/  audio_codec; } ;
struct hdpvr_device {scalar_t__ status; TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ HDPVR_AUDIO_INPUTS ; 
 scalar_t__ STATUS_IDLE ; 
 int hdpvr_set_audio (struct hdpvr_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_audio(struct file *file, void *private_data,
			  const struct v4l2_audio *audio)
{
	struct hdpvr_device *dev = video_drvdata(file);
	int retval;

	if (audio->index >= HDPVR_AUDIO_INPUTS)
		return -EINVAL;

	if (dev->status != STATUS_IDLE)
		return -EBUSY;

	retval = hdpvr_set_audio(dev, audio->index+1, dev->options.audio_codec);
	if (!retval)
		dev->options.audio_input = audio->index;

	return retval;
}