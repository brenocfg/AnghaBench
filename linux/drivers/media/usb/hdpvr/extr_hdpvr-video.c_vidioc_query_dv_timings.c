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
struct v4l2_bt_timings {scalar_t__ width; scalar_t__ height; int interlaced; scalar_t__ pixelclock; } ;
struct v4l2_dv_timings {struct v4l2_bt_timings bt; } ;
struct hdpvr_video_info {int fps; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  valid; } ;
struct hdpvr_fh {int legacy_mode; } ;
struct TYPE_2__ {scalar_t__ video_input; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct v4l2_dv_timings*) ; 
 int ENODATA ; 
 int ENOLCK ; 
 int ERANGE ; 
 unsigned int V4L2_DV_BT_FRAME_HEIGHT (struct v4l2_bt_timings const*) ; 
 unsigned int V4L2_DV_BT_FRAME_WIDTH (struct v4l2_bt_timings const*) ; 
 int get_video_info (struct hdpvr_device*,struct hdpvr_video_info*) ; 
 struct v4l2_dv_timings* hdpvr_dv_timings ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_query_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	struct hdpvr_video_info vid_info;
	bool interlaced;
	int ret = 0;
	int i;

	fh->legacy_mode = false;
	if (dev->options.video_input)
		return -ENODATA;
	ret = get_video_info(dev, &vid_info);
	if (ret)
		return ret;
	if (!vid_info.valid)
		return -ENOLCK;
	interlaced = vid_info.fps <= 30;
	for (i = 0; i < ARRAY_SIZE(hdpvr_dv_timings); i++) {
		const struct v4l2_bt_timings *bt = &hdpvr_dv_timings[i].bt;
		unsigned hsize;
		unsigned vsize;
		unsigned fps;

		hsize = V4L2_DV_BT_FRAME_WIDTH(bt);
		vsize = V4L2_DV_BT_FRAME_HEIGHT(bt);
		fps = (unsigned)bt->pixelclock / (hsize * vsize);
		if (bt->width != vid_info.width ||
		    bt->height != vid_info.height ||
		    bt->interlaced != interlaced ||
		    (fps != vid_info.fps && fps + 1 != vid_info.fps))
			continue;
		*timings = hdpvr_dv_timings[i];
		break;
	}
	if (i == ARRAY_SIZE(hdpvr_dv_timings))
		ret = -ERANGE;

	return ret;
}