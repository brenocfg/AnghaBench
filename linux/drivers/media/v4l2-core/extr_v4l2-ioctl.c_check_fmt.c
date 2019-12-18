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
struct video_device {scalar_t__ vfl_type; scalar_t__ vfl_dir; struct v4l2_ioctl_ops* ioctl_ops; } ;
struct v4l2_ioctl_ops {int /*<<< orphan*/  vidioc_g_fmt_meta_out; int /*<<< orphan*/  vidioc_g_fmt_meta_cap; int /*<<< orphan*/  vidioc_g_fmt_sdr_out; int /*<<< orphan*/  vidioc_g_fmt_sdr_cap; int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_out; int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_cap; int /*<<< orphan*/  vidioc_g_fmt_vbi_out; int /*<<< orphan*/  vidioc_g_fmt_vbi_cap; int /*<<< orphan*/  vidioc_g_fmt_vid_out_overlay; int /*<<< orphan*/  vidioc_g_fmt_vid_out_mplane; int /*<<< orphan*/  vidioc_g_fmt_vid_out; int /*<<< orphan*/  vidioc_g_fmt_vid_overlay; int /*<<< orphan*/  vidioc_g_fmt_vid_cap_mplane; int /*<<< orphan*/  vidioc_g_fmt_vid_cap; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_META_CAPTURE 141 
#define  V4L2_BUF_TYPE_META_OUTPUT 140 
#define  V4L2_BUF_TYPE_SDR_CAPTURE 139 
#define  V4L2_BUF_TYPE_SDR_OUTPUT 138 
#define  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE 137 
#define  V4L2_BUF_TYPE_SLICED_VBI_OUTPUT 136 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 135 
#define  V4L2_BUF_TYPE_VBI_OUTPUT 134 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 133 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 132 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 131 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY 129 
#define  V4L2_BUF_TYPE_VIDEO_OVERLAY 128 
 scalar_t__ VFL_DIR_RX ; 
 scalar_t__ VFL_DIR_TX ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 scalar_t__ VFL_TYPE_SDR ; 
 scalar_t__ VFL_TYPE_TOUCH ; 
 scalar_t__ VFL_TYPE_VBI ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int check_fmt(struct file *file, enum v4l2_buf_type type)
{
	struct video_device *vfd = video_devdata(file);
	const struct v4l2_ioctl_ops *ops = vfd->ioctl_ops;
	bool is_vid = vfd->vfl_type == VFL_TYPE_GRABBER;
	bool is_vbi = vfd->vfl_type == VFL_TYPE_VBI;
	bool is_sdr = vfd->vfl_type == VFL_TYPE_SDR;
	bool is_tch = vfd->vfl_type == VFL_TYPE_TOUCH;
	bool is_rx = vfd->vfl_dir != VFL_DIR_TX;
	bool is_tx = vfd->vfl_dir != VFL_DIR_RX;

	if (ops == NULL)
		return -EINVAL;

	switch (type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		if ((is_vid || is_tch) && is_rx &&
		    (ops->vidioc_g_fmt_vid_cap || ops->vidioc_g_fmt_vid_cap_mplane))
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		if (is_vid && is_rx && ops->vidioc_g_fmt_vid_cap_mplane)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OVERLAY:
		if (is_vid && is_rx && ops->vidioc_g_fmt_vid_overlay)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		if (is_vid && is_tx &&
		    (ops->vidioc_g_fmt_vid_out || ops->vidioc_g_fmt_vid_out_mplane))
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		if (is_vid && is_tx && ops->vidioc_g_fmt_vid_out_mplane)
			return 0;
		break;
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_OVERLAY:
		if (is_vid && is_tx && ops->vidioc_g_fmt_vid_out_overlay)
			return 0;
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
		if (is_vbi && is_rx && ops->vidioc_g_fmt_vbi_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		if (is_vbi && is_tx && ops->vidioc_g_fmt_vbi_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
		if (is_vbi && is_rx && ops->vidioc_g_fmt_sliced_vbi_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		if (is_vbi && is_tx && ops->vidioc_g_fmt_sliced_vbi_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_SDR_CAPTURE:
		if (is_sdr && is_rx && ops->vidioc_g_fmt_sdr_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_SDR_OUTPUT:
		if (is_sdr && is_tx && ops->vidioc_g_fmt_sdr_out)
			return 0;
		break;
	case V4L2_BUF_TYPE_META_CAPTURE:
		if (is_vid && is_rx && ops->vidioc_g_fmt_meta_cap)
			return 0;
		break;
	case V4L2_BUF_TYPE_META_OUTPUT:
		if (is_vid && is_tx && ops->vidioc_g_fmt_meta_out)
			return 0;
		break;
	default:
		break;
	}
	return -EINVAL;
}