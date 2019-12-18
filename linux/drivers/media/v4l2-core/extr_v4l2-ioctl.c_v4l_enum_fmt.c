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
typedef  int u32 ;
struct video_device {int device_caps; } ;
struct v4l2_ioctl_ops {int (* vidioc_enum_fmt_vid_cap ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_vid_overlay ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_vid_out ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_sdr_cap ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_sdr_out ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_meta_cap ) (struct file*,void*,void*) ;int (* vidioc_enum_fmt_meta_out ) (struct file*,void*,void*) ;} ;
struct v4l2_fmtdesc {int type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_META_CAPTURE 136 
#define  V4L2_BUF_TYPE_META_OUTPUT 135 
#define  V4L2_BUF_TYPE_SDR_CAPTURE 134 
#define  V4L2_BUF_TYPE_SDR_OUTPUT 133 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 132 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 131 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 129 
#define  V4L2_BUF_TYPE_VIDEO_OVERLAY 128 
 int V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_CAP_VIDEO_M2M_MPLANE ; 
 int V4L2_CAP_VIDEO_OUTPUT_MPLANE ; 
 int check_fmt (struct file*,int) ; 
 int stub1 (struct file*,void*,void*) ; 
 int stub2 (struct file*,void*,void*) ; 
 int stub3 (struct file*,void*,void*) ; 
 int stub4 (struct file*,void*,void*) ; 
 int stub5 (struct file*,void*,void*) ; 
 int stub6 (struct file*,void*,void*) ; 
 int stub7 (struct file*,void*,void*) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int /*<<< orphan*/  v4l_fill_fmtdesc (struct v4l2_fmtdesc*) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int v4l_enum_fmt(const struct v4l2_ioctl_ops *ops,
				struct file *file, void *fh, void *arg)
{
	struct video_device *vdev = video_devdata(file);
	struct v4l2_fmtdesc *p = arg;
	int ret = check_fmt(file, p->type);
	u32 cap_mask;

	if (ret)
		return ret;
	ret = -EINVAL;

	switch (p->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		cap_mask = V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			   V4L2_CAP_VIDEO_M2M_MPLANE;
		if (!!(vdev->device_caps & cap_mask) !=
		    (p->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE))
			break;

		if (unlikely(!ops->vidioc_enum_fmt_vid_cap))
			break;
		ret = ops->vidioc_enum_fmt_vid_cap(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
		if (unlikely(!ops->vidioc_enum_fmt_vid_overlay))
			break;
		ret = ops->vidioc_enum_fmt_vid_overlay(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		cap_mask = V4L2_CAP_VIDEO_OUTPUT_MPLANE |
			   V4L2_CAP_VIDEO_M2M_MPLANE;
		if (!!(vdev->device_caps & cap_mask) !=
		    (p->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE))
			break;

		if (unlikely(!ops->vidioc_enum_fmt_vid_out))
			break;
		ret = ops->vidioc_enum_fmt_vid_out(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_SDR_CAPTURE:
		if (unlikely(!ops->vidioc_enum_fmt_sdr_cap))
			break;
		ret = ops->vidioc_enum_fmt_sdr_cap(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_SDR_OUTPUT:
		if (unlikely(!ops->vidioc_enum_fmt_sdr_out))
			break;
		ret = ops->vidioc_enum_fmt_sdr_out(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_META_CAPTURE:
		if (unlikely(!ops->vidioc_enum_fmt_meta_cap))
			break;
		ret = ops->vidioc_enum_fmt_meta_cap(file, fh, arg);
		break;
	case V4L2_BUF_TYPE_META_OUTPUT:
		if (unlikely(!ops->vidioc_enum_fmt_meta_out))
			break;
		ret = ops->vidioc_enum_fmt_meta_out(file, fh, arg);
		break;
	}
	if (ret == 0)
		v4l_fill_fmtdesc(p);
	return ret;
}