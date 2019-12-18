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
struct TYPE_4__ {int min_width; int max_width; int min_height; int max_height; int min_pixelclock; int max_pixelclock; int capabilities; int /*<<< orphan*/  standards; } ;
struct v4l2_dv_timings_cap {TYPE_2__ bt; int /*<<< orphan*/  type; } ;
struct hdpvr_fh {int legacy_mode; } ;
struct TYPE_3__ {scalar_t__ video_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  V4L2_DV_BT_656_1120 ; 
 int V4L2_DV_BT_CAP_INTERLACED ; 
 int V4L2_DV_BT_CAP_PROGRESSIVE ; 
 int /*<<< orphan*/  V4L2_DV_BT_STD_CEA861 ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_dv_timings_cap(struct file *file, void *_fh,
				    struct v4l2_dv_timings_cap *cap)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	if (dev->options.video_input)
		return -ENODATA;
	cap->type = V4L2_DV_BT_656_1120;
	cap->bt.min_width = 720;
	cap->bt.max_width = 1920;
	cap->bt.min_height = 480;
	cap->bt.max_height = 1080;
	cap->bt.min_pixelclock = 27000000;
	cap->bt.max_pixelclock = 74250000;
	cap->bt.standards = V4L2_DV_BT_STD_CEA861;
	cap->bt.capabilities = V4L2_DV_BT_CAP_INTERLACED | V4L2_DV_BT_CAP_PROGRESSIVE;
	return 0;
}