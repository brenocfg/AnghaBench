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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct hdpvr_video_info {int width; int height; scalar_t__ valid; } ;
struct hdpvr_fh {scalar_t__ legacy_mode; } ;
struct TYPE_2__ {scalar_t__ video_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ HDPVR_COMPONENT ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_STD_625_50 ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 int get_video_info (struct hdpvr_device*,struct hdpvr_video_info*) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querystd(struct file *file, void *_fh, v4l2_std_id *a)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_video_info vid_info;
	struct hdpvr_fh *fh = _fh;
	int ret;

	*a = V4L2_STD_UNKNOWN;
	if (dev->options.video_input == HDPVR_COMPONENT)
		return fh->legacy_mode ? 0 : -ENODATA;
	ret = get_video_info(dev, &vid_info);
	if (vid_info.valid && vid_info.width == 720 &&
	    (vid_info.height == 480 || vid_info.height == 576)) {
		*a = (vid_info.height == 480) ?
			V4L2_STD_525_60 : V4L2_STD_625_50;
	}
	return ret;
}