#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct video_device {int device_caps; int /*<<< orphan*/ * lock; struct vb2_queue* queue; int /*<<< orphan*/  vfl_dir; TYPE_10__* v4l2_dev; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; int /*<<< orphan*/  release; int /*<<< orphan*/  name; int /*<<< orphan*/  tvnorms; } ;
struct vb2_queue {int io_modes; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct unicam_device* drv_priv; int /*<<< orphan*/  type; } ;
struct v4l2_mbus_framefmt {scalar_t__ field; int /*<<< orphan*/  code; int /*<<< orphan*/  member_0; } ;
struct unicam_fmt {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  code; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  notify; } ;
struct TYPE_13__ {int /*<<< orphan*/  ctrls; } ;
struct TYPE_18__ {int /*<<< orphan*/  active; } ;
struct TYPE_14__ {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_15__ {TYPE_1__ pix; } ;
struct TYPE_16__ {TYPE_2__ fmt; } ;
struct unicam_device {struct video_device video_dev; TYPE_10__ v4l2_dev; TYPE_6__* sensor; TYPE_11__ ctrl_handler; int /*<<< orphan*/  lock; TYPE_5__ dma_queue; TYPE_4__* pdev; struct vb2_queue buffer_queue; int /*<<< orphan*/  dma_queue_lock; TYPE_3__ v_fmt; struct unicam_fmt const* fmt; struct unicam_fmt* active_fmts; int /*<<< orphan*/  sensor_config; } ;
struct unicam_buffer {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNICAM_MODULE_NAME ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VIDIOC_DV_TIMINGS_CAP ; 
 int /*<<< orphan*/  VIDIOC_ENUMSTD ; 
 int /*<<< orphan*/  VIDIOC_ENUM_DV_TIMINGS ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FRAMEINTERVALS ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FRAMESIZES ; 
 int /*<<< orphan*/  VIDIOC_G_DV_TIMINGS ; 
 int /*<<< orphan*/  VIDIOC_G_EDID ; 
 int /*<<< orphan*/  VIDIOC_G_PARM ; 
 int /*<<< orphan*/  VIDIOC_G_STD ; 
 int /*<<< orphan*/  VIDIOC_QUERYSTD ; 
 int /*<<< orphan*/  VIDIOC_QUERY_DV_TIMINGS ; 
 int /*<<< orphan*/  VIDIOC_S_DV_TIMINGS ; 
 int /*<<< orphan*/  VIDIOC_S_EDID ; 
 int /*<<< orphan*/  VIDIOC_S_PARM ; 
 int /*<<< orphan*/  VIDIOC_S_STD ; 
 scalar_t__ WARN_ON (int) ; 
 int __subdev_get_format (struct unicam_device*,struct v4l2_mbus_framefmt*) ; 
 int __subdev_set_format (struct unicam_device*,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 int /*<<< orphan*/  enum_frame_size ; 
 struct unicam_fmt* find_format_by_code (struct unicam_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_frame_interval ; 
 int /*<<< orphan*/  g_tvnorms ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  s_dv_timings ; 
 int /*<<< orphan*/  s_frame_interval ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unicam_err (struct unicam_device*,char*,...) ; 
 int /*<<< orphan*/  unicam_fops ; 
 int /*<<< orphan*/  unicam_ioctl_ops ; 
 int /*<<< orphan*/  unicam_notify ; 
 int /*<<< orphan*/  unicam_reset_format (struct unicam_device*) ; 
 int /*<<< orphan*/  unicam_video_qops ; 
 int v4l2_ctrl_add_handler (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_device_register_subdev_nodes (TYPE_10__*) ; 
 int /*<<< orphan*/  v4l2_disable_ioctl (struct video_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdev_hostdata (TYPE_6__*,struct unicam_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_alloc_pad_config (TYPE_6__*) ; 
 int v4l2_subdev_call (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_subdev_has_op (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  video ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct unicam_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int unicam_probe_complete(struct unicam_device *unicam)
{
	struct video_device *vdev;
	struct vb2_queue *q;
	struct v4l2_mbus_framefmt mbus_fmt = {0};
	const struct unicam_fmt *fmt;
	int ret;

	v4l2_set_subdev_hostdata(unicam->sensor, unicam);

	unicam->v4l2_dev.notify = unicam_notify;

	unicam->sensor_config = v4l2_subdev_alloc_pad_config(unicam->sensor);
	if (!unicam->sensor_config)
		return -ENOMEM;

	ret = __subdev_get_format(unicam, &mbus_fmt);
	if (ret) {
		unicam_err(unicam, "Failed to get_format - ret %d\n", ret);
		return ret;
	}

	fmt = find_format_by_code(unicam, mbus_fmt.code);
	if (!fmt) {
		/* Default image format not valid. Choose first active fmt. */
		fmt = &unicam->active_fmts[0];
		mbus_fmt.code = fmt->code;
		ret = __subdev_set_format(unicam, &mbus_fmt);
		if (ret)
			return -EINVAL;
	}
	if (mbus_fmt.field != V4L2_FIELD_NONE) {
		/* Interlaced not supported - disable it now. */
		mbus_fmt.field = V4L2_FIELD_NONE;
		ret = __subdev_set_format(unicam, &mbus_fmt);
		if (ret)
			return -EINVAL;
	}

	unicam->fmt = fmt;
	unicam->v_fmt.fmt.pix.pixelformat = fmt->fourcc;

	/* Read current subdev format */
	unicam_reset_format(unicam);

	if (v4l2_subdev_has_op(unicam->sensor, video, s_std)) {
		v4l2_std_id tvnorms;

		if (WARN_ON(!v4l2_subdev_has_op(unicam->sensor, video,
						g_tvnorms)))
			/*
			 * Subdevice should not advertise s_std but not
			 * g_tvnorms
			 */
			return -EINVAL;

		ret = v4l2_subdev_call(unicam->sensor, video,
				       g_tvnorms, &tvnorms);
		if (WARN_ON(ret))
			return -EINVAL;
		unicam->video_dev.tvnorms |= tvnorms;
	}

	spin_lock_init(&unicam->dma_queue_lock);
	mutex_init(&unicam->lock);

	/* Add controls from the subdevice */
	ret = v4l2_ctrl_add_handler(&unicam->ctrl_handler,
				    unicam->sensor->ctrl_handler, NULL);
	if (ret < 0)
		return ret;

	q = &unicam->buffer_queue;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_DMABUF | VB2_READ;
	q->drv_priv = unicam;
	q->ops = &unicam_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_struct_size = sizeof(struct unicam_buffer);
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &unicam->lock;
	q->min_buffers_needed = 2;
	q->dev = &unicam->pdev->dev;

	ret = vb2_queue_init(q);
	if (ret) {
		unicam_err(unicam, "vb2_queue_init() failed\n");
		return ret;
	}

	INIT_LIST_HEAD(&unicam->dma_queue.active);

	vdev = &unicam->video_dev;
	strlcpy(vdev->name, UNICAM_MODULE_NAME, sizeof(vdev->name));
	vdev->release = video_device_release_empty;
	vdev->fops = &unicam_fops;
	vdev->ioctl_ops = &unicam_ioctl_ops;
	vdev->v4l2_dev = &unicam->v4l2_dev;
	vdev->vfl_dir = VFL_DIR_RX;
	vdev->queue = q;
	vdev->lock = &unicam->lock;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING |
			    V4L2_CAP_READWRITE;

	/* If the source has no controls then remove our ctrl handler. */
	if (list_empty(&unicam->ctrl_handler.ctrls))
		unicam->v4l2_dev.ctrl_handler = NULL;

	video_set_drvdata(vdev, unicam);
	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret) {
		unicam_err(unicam, "Unable to register video device.\n");
		return ret;
	}

	if (!v4l2_subdev_has_op(unicam->sensor, video, s_std)) {
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_S_STD);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_G_STD);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_ENUMSTD);
	}
	if (!v4l2_subdev_has_op(unicam->sensor, video, querystd))
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_QUERYSTD);
	if (!v4l2_subdev_has_op(unicam->sensor, video, s_dv_timings)) {
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_S_EDID);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_G_EDID);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_DV_TIMINGS_CAP);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_G_DV_TIMINGS);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_S_DV_TIMINGS);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_ENUM_DV_TIMINGS);
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_QUERY_DV_TIMINGS);
	}
	if (!v4l2_subdev_has_op(unicam->sensor, pad, enum_frame_interval))
		v4l2_disable_ioctl(&unicam->video_dev,
				   VIDIOC_ENUM_FRAMEINTERVALS);
	if (!v4l2_subdev_has_op(unicam->sensor, video, g_frame_interval))
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_G_PARM);
	if (!v4l2_subdev_has_op(unicam->sensor, video, s_frame_interval))
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_S_PARM);

	if (!v4l2_subdev_has_op(unicam->sensor, pad, enum_frame_size))
		v4l2_disable_ioctl(&unicam->video_dev, VIDIOC_ENUM_FRAMESIZES);

	ret = v4l2_device_register_subdev_nodes(&unicam->v4l2_dev);
	if (ret) {
		unicam_err(unicam,
			   "Unable to register subdev nodes.\n");
		video_unregister_device(&unicam->video_dev);
		return ret;
	}

	return 0;
}