#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct v4l2_dv_timings {int dummy; } ;
struct hdpvr_fh {int legacy_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_2__ bt; } ;
struct TYPE_6__ {scalar_t__ video_input; } ;
struct hdpvr_device {scalar_t__ status; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__ cur_dv_timings; TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 scalar_t__ STATUS_IDLE ; 
 TYPE_3__* hdpvr_dv_timings ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;
	int i;

	fh->legacy_mode = false;
	if (dev->options.video_input)
		return -ENODATA;
	if (dev->status != STATUS_IDLE)
		return -EBUSY;
	for (i = 0; i < ARRAY_SIZE(hdpvr_dv_timings); i++)
		if (v4l2_match_dv_timings(timings, hdpvr_dv_timings + i, 0, false))
			break;
	if (i == ARRAY_SIZE(hdpvr_dv_timings))
		return -EINVAL;
	dev->cur_dv_timings = hdpvr_dv_timings[i];
	dev->width = hdpvr_dv_timings[i].bt.width;
	dev->height = hdpvr_dv_timings[i].bt.height;
	return 0;
}