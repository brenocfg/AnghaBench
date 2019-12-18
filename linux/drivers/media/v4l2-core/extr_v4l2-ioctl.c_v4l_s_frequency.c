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
struct v4l2_ioctl_ops {int (* vidioc_s_frequency ) (struct file*,void*,struct v4l2_frequency const*) ;} ;
struct v4l2_frequency {scalar_t__ type; } ;
struct file {int dummy; } ;
typedef  enum v4l2_tuner_type { ____Placeholder_v4l2_tuner_type } v4l2_tuner_type ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_TUNER_ANALOG_TV ; 
 int V4L2_TUNER_RADIO ; 
 scalar_t__ V4L2_TUNER_RF ; 
 scalar_t__ V4L2_TUNER_SDR ; 
 scalar_t__ VFL_TYPE_RADIO ; 
 scalar_t__ VFL_TYPE_SDR ; 
 int stub1 (struct file*,void*,struct v4l2_frequency const*) ; 
 int v4l_enable_media_source (struct video_device*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_s_frequency(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vfd = video_devdata(file);
	const struct v4l2_frequency *p = arg;
	enum v4l2_tuner_type type;
	int ret;

	ret = v4l_enable_media_source(vfd);
	if (ret)
		return ret;
	if (vfd->vfl_type == VFL_TYPE_SDR) {
		if (p->type != V4L2_TUNER_SDR && p->type != V4L2_TUNER_RF)
			return -EINVAL;
	} else {
		type = (vfd->vfl_type == VFL_TYPE_RADIO) ?
				V4L2_TUNER_RADIO : V4L2_TUNER_ANALOG_TV;
		if (type != p->type)
			return -EINVAL;
	}
	return ops->vidioc_s_frequency(file, fh, p);
}