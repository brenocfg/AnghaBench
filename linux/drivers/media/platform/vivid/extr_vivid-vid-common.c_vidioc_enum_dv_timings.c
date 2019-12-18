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
struct vivid_dev {int dummy; } ;
struct video_device {scalar_t__ vfl_dir; } ;
struct v4l2_enum_dv_timings {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ VFL_DIR_RX ; 
 int v4l2_enum_dv_timings_cap (struct v4l2_enum_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_dv_timings_cap ; 
 int /*<<< orphan*/  vivid_is_hdmi_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_is_hdmi_out (struct vivid_dev*) ; 

int vidioc_enum_dv_timings(struct file *file, void *_fh,
				    struct v4l2_enum_dv_timings *timings)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	if (vdev->vfl_dir == VFL_DIR_RX) {
		if (!vivid_is_hdmi_cap(dev))
			return -ENODATA;
	} else {
		if (!vivid_is_hdmi_out(dev))
			return -ENODATA;
	}
	return v4l2_enum_dv_timings_cap(timings, &vivid_dv_timings_cap,
			NULL, NULL);
}