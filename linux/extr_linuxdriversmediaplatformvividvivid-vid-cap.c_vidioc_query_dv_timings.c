#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pixelclock; } ;
struct v4l2_dv_timings {TYPE_1__ bt; } ;
struct vivid_dev {scalar_t__ dv_timings_signal_mode; scalar_t__ edid_blocks; size_t query_dv_timings; size_t query_dv_timings_last; int query_dv_timings_size; struct v4l2_dv_timings dv_timings_cap; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int max_pixelclock; } ;
struct TYPE_6__ {TYPE_2__ bt; } ;

/* Variables and functions */
 scalar_t__ CURRENT_DV_TIMINGS ; 
 int ENODATA ; 
 int ENOLCK ; 
 int ENOLINK ; 
 int ERANGE ; 
 scalar_t__ NO_LOCK ; 
 scalar_t__ NO_SIGNAL ; 
 scalar_t__ OUT_OF_RANGE ; 
 scalar_t__ SELECTED_DV_TIMINGS ; 
 struct v4l2_dv_timings* v4l2_dv_timings_presets ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 TYPE_3__ vivid_dv_timings_cap ; 
 int /*<<< orphan*/  vivid_is_hdmi_cap (struct vivid_dev*) ; 

int vidioc_query_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!vivid_is_hdmi_cap(dev))
		return -ENODATA;
	if (dev->dv_timings_signal_mode == NO_SIGNAL ||
	    dev->edid_blocks == 0)
		return -ENOLINK;
	if (dev->dv_timings_signal_mode == NO_LOCK)
		return -ENOLCK;
	if (dev->dv_timings_signal_mode == OUT_OF_RANGE) {
		timings->bt.pixelclock = vivid_dv_timings_cap.bt.max_pixelclock * 2;
		return -ERANGE;
	}
	if (dev->dv_timings_signal_mode == CURRENT_DV_TIMINGS) {
		*timings = dev->dv_timings_cap;
	} else if (dev->dv_timings_signal_mode == SELECTED_DV_TIMINGS) {
		*timings = v4l2_dv_timings_presets[dev->query_dv_timings];
	} else {
		*timings = v4l2_dv_timings_presets[dev->query_dv_timings_last];
		dev->query_dv_timings_last = (dev->query_dv_timings_last + 1) %
						dev->query_dv_timings_size;
	}
	return 0;
}