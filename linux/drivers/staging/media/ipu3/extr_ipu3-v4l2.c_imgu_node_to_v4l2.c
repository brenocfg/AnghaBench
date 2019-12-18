#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct video_device {int device_caps; int /*<<< orphan*/ * ioctl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  dataformat; } ;
struct TYPE_3__ {TYPE_2__ meta; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;

/* Variables and functions */
#define  IMGU_NODE_IN 130 
 int IMGU_NODE_NUM ; 
#define  IMGU_NODE_PARAMS 129 
#define  IMGU_NODE_STAT_3A 128 
 int /*<<< orphan*/  V4L2_BUF_TYPE_META_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_META_OUTPUT ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int V4L2_CAP_META_CAPTURE ; 
 int V4L2_CAP_META_OUTPUT ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_CAP_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  V4L2_META_FMT_IPU3_PARAMS ; 
 int /*<<< orphan*/  V4L2_META_FMT_IPU3_STAT_3A ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  imgu_css_meta_fmt_set (TYPE_2__*) ; 
 int /*<<< orphan*/  imgu_v4l2_ioctl_ops ; 
 int /*<<< orphan*/  imgu_v4l2_meta_ioctl_ops ; 

__attribute__((used)) static void imgu_node_to_v4l2(u32 node, struct video_device *vdev,
			      struct v4l2_format *f)
{
	u32 cap;

	/* Should not happen */
	WARN_ON(node >= IMGU_NODE_NUM);

	switch (node) {
	case IMGU_NODE_IN:
		cap = V4L2_CAP_VIDEO_OUTPUT_MPLANE;
		f->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
		vdev->ioctl_ops = &imgu_v4l2_ioctl_ops;
		break;
	case IMGU_NODE_PARAMS:
		cap = V4L2_CAP_META_OUTPUT;
		f->type = V4L2_BUF_TYPE_META_OUTPUT;
		f->fmt.meta.dataformat = V4L2_META_FMT_IPU3_PARAMS;
		vdev->ioctl_ops = &imgu_v4l2_meta_ioctl_ops;
		imgu_css_meta_fmt_set(&f->fmt.meta);
		break;
	case IMGU_NODE_STAT_3A:
		cap = V4L2_CAP_META_CAPTURE;
		f->type = V4L2_BUF_TYPE_META_CAPTURE;
		f->fmt.meta.dataformat = V4L2_META_FMT_IPU3_STAT_3A;
		vdev->ioctl_ops = &imgu_v4l2_meta_ioctl_ops;
		imgu_css_meta_fmt_set(&f->fmt.meta);
		break;
	default:
		cap = V4L2_CAP_VIDEO_CAPTURE_MPLANE;
		f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		vdev->ioctl_ops = &imgu_v4l2_ioctl_ops;
	}

	vdev->device_caps = V4L2_CAP_STREAMING | cap;
}