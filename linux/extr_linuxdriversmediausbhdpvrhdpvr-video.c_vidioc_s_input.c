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
struct TYPE_2__ {unsigned int video_input; } ;
struct hdpvr_device {scalar_t__ status; TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_VIDEO_INPUT_VALUE ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int HDPVR_VIDEO_INPUTS ; 
 scalar_t__ STATUS_IDLE ; 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,unsigned int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_input(struct file *file, void *_fh,
			  unsigned int index)
{
	struct hdpvr_device *dev = video_drvdata(file);
	int retval;

	if (index >= HDPVR_VIDEO_INPUTS)
		return -EINVAL;

	if (dev->status != STATUS_IDLE)
		return -EBUSY;

	retval = hdpvr_config_call(dev, CTRL_VIDEO_INPUT_VALUE, index+1);
	if (!retval) {
		dev->options.video_input = index;
		/*
		 * Unfortunately gstreamer calls ENUMSTD and bails out if it
		 * won't find any formats, even though component input is
		 * selected. This means that we have to leave tvnorms at
		 * V4L2_STD_ALL. We cannot use the 'legacy' trick since
		 * tvnorms is set at the device node level and not at the
		 * filehandle level.
		 *
		 * Comment this out for now, but if the legacy mode can be
		 * removed in the future, then this code should be enabled
		 * again.
		dev->video_dev.tvnorms =
			(index != HDPVR_COMPONENT) ? V4L2_STD_ALL : 0;
		 */
	}

	return retval;
}