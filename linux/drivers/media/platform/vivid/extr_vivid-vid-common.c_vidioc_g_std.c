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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct vivid_dev {size_t input; int /*<<< orphan*/  std_out; int /*<<< orphan*/ * std_cap; } ;
struct video_device {scalar_t__ vfl_dir; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ VFL_DIR_RX ; 
 struct video_device* video_devdata (struct file*) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vivid_is_sdtv_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_is_svid_out (struct vivid_dev*) ; 

int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct vivid_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	if (vdev->vfl_dir == VFL_DIR_RX) {
		if (!vivid_is_sdtv_cap(dev))
			return -ENODATA;
		*id = dev->std_cap[dev->input];
	} else {
		if (!vivid_is_svid_out(dev))
			return -ENODATA;
		*id = dev->std_out;
	}
	return 0;
}