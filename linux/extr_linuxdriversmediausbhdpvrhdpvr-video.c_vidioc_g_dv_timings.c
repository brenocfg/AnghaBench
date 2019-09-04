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
struct v4l2_dv_timings {int dummy; } ;
struct hdpvr_fh {int legacy_mode; } ;
struct TYPE_2__ {scalar_t__ video_input; } ;
struct hdpvr_device {struct v4l2_dv_timings cur_dv_timings; TYPE_1__ options; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 struct hdpvr_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_dv_timings(struct file *file, void *_fh,
				    struct v4l2_dv_timings *timings)
{
	struct hdpvr_device *dev = video_drvdata(file);
	struct hdpvr_fh *fh = _fh;

	fh->legacy_mode = false;
	if (dev->options.video_input)
		return -ENODATA;
	*timings = dev->cur_dv_timings;
	return 0;
}