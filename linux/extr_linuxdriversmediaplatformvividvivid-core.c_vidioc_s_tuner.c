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
struct video_device {scalar_t__ vfl_type; } ;
struct v4l2_tuner {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ VFL_TYPE_RADIO ; 
 scalar_t__ VFL_TYPE_SDR ; 
 struct video_device* video_devdata (struct file*) ; 
 int vivid_radio_rx_s_tuner (struct file*,void*,struct v4l2_tuner const*) ; 
 int vivid_sdr_s_tuner (struct file*,void*,struct v4l2_tuner const*) ; 
 int vivid_video_s_tuner (struct file*,void*,struct v4l2_tuner const*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *fh, const struct v4l2_tuner *vt)
{
	struct video_device *vdev = video_devdata(file);

	if (vdev->vfl_type == VFL_TYPE_RADIO)
		return vivid_radio_rx_s_tuner(file, fh, vt);
	if (vdev->vfl_type == VFL_TYPE_SDR)
		return vivid_sdr_s_tuner(file, fh, vt);
	return vivid_video_s_tuner(file, fh, vt);
}