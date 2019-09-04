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
typedef  int v4l2_std_id ;
typedef  int u8 ;
struct hdpvr_fh {int /*<<< orphan*/  legacy_mode; } ;
struct TYPE_2__ {scalar_t__ video_input; } ;
struct hdpvr_device {scalar_t__ status; int cur_std; int width; int height; TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_VIDEO_STD_TYPE ; 
 int EBUSY ; 
 int ENODATA ; 
 scalar_t__ HDPVR_COMPONENT ; 
 scalar_t__ STATUS_IDLE ; 
 int V4L2_STD_525_60 ; 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *_fh,
			v4l2_std_id std)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	u8 std_type = 1;

	if (!fh->legacy_mode && dev->options.video_input == HDPVR_COMPONENT)
		return -ENODATA;
	if (dev->status != STATUS_IDLE)
		return -EBUSY;
	if (std & V4L2_STD_525_60)
		std_type = 0;
	dev->cur_std = std;
	dev->width = 720;
	dev->height = std_type ? 576 : 480;

	return hdpvr_config_call(dev, CTRL_VIDEO_STD_TYPE, std_type);
}