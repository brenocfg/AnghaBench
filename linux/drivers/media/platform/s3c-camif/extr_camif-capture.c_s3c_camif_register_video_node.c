#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct video_device {int minor; int io_modes; int buf_struct_size; int device_caps; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; TYPE_3__* ctrl_handler; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; struct camif_vp* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; int /*<<< orphan*/  release; TYPE_2__* v4l2_dev; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct vb2_queue {int minor; int io_modes; int buf_struct_size; int device_caps; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; TYPE_3__* ctrl_handler; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; struct camif_vp* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; int /*<<< orphan*/  release; TYPE_2__* v4l2_dev; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct v4l2_ctrl {struct camif_vp* priv; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct camif_vp {scalar_t__ id; TYPE_3__ ctrl_handler; TYPE_6__ pad; TYPE_1__* camif; int /*<<< orphan*/  active_buf_q; int /*<<< orphan*/  pending_buf_q; scalar_t__ reqbufs_count; struct video_device vdev; struct video_device vb_queue; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct camif_dev {TYPE_2__ v4l2_dev; int /*<<< orphan*/  lock; struct camif_vp* vp; } ;
struct camif_buffer {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s3c_camif_fops ; 
 int /*<<< orphan*/  s3c_camif_ioctl_ops ; 
 int /*<<< orphan*/  s3c_camif_qops ; 
 int /*<<< orphan*/  s3c_camif_video_ctrl_ops ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct video_device*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct camif_vp*) ; 

int s3c_camif_register_video_node(struct camif_dev *camif, int idx)
{
	struct camif_vp *vp = &camif->vp[idx];
	struct vb2_queue *q = &vp->vb_queue;
	struct video_device *vfd = &vp->vdev;
	struct v4l2_ctrl *ctrl;
	int ret;

	memset(vfd, 0, sizeof(*vfd));
	snprintf(vfd->name, sizeof(vfd->name), "camif-%s",
		 vp->id == 0 ? "codec" : "preview");

	vfd->fops = &s3c_camif_fops;
	vfd->ioctl_ops = &s3c_camif_ioctl_ops;
	vfd->v4l2_dev = &camif->v4l2_dev;
	vfd->minor = -1;
	vfd->release = video_device_release_empty;
	vfd->lock = &camif->lock;
	vp->reqbufs_count = 0;

	INIT_LIST_HEAD(&vp->pending_buf_q);
	INIT_LIST_HEAD(&vp->active_buf_q);

	memset(q, 0, sizeof(*q));
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->ops = &s3c_camif_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_struct_size = sizeof(struct camif_buffer);
	q->drv_priv = vp;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &vp->camif->lock;
	q->dev = camif->v4l2_dev.dev;

	ret = vb2_queue_init(q);
	if (ret)
		goto err_vd_rel;

	vp->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vfd->entity, 1, &vp->pad);
	if (ret)
		goto err_vd_rel;

	video_set_drvdata(vfd, vp);

	v4l2_ctrl_handler_init(&vp->ctrl_handler, 1);
	ctrl = v4l2_ctrl_new_std(&vp->ctrl_handler, &s3c_camif_video_ctrl_ops,
				 V4L2_CID_HFLIP, 0, 1, 1, 0);
	if (ctrl)
		ctrl->priv = vp;
	ctrl = v4l2_ctrl_new_std(&vp->ctrl_handler, &s3c_camif_video_ctrl_ops,
				 V4L2_CID_VFLIP, 0, 1, 1, 0);
	if (ctrl)
		ctrl->priv = vp;

	ret = vp->ctrl_handler.error;
	if (ret < 0)
		goto err_me_cleanup;

	vfd->ctrl_handler = &vp->ctrl_handler;
	vfd->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_VIDEO_CAPTURE;

	ret = video_register_device(vfd, VFL_TYPE_GRABBER, -1);
	if (ret)
		goto err_ctrlh_free;

	v4l2_info(&camif->v4l2_dev, "registered %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	return 0;

err_ctrlh_free:
	v4l2_ctrl_handler_free(&vp->ctrl_handler);
err_me_cleanup:
	media_entity_cleanup(&vfd->entity);
err_vd_rel:
	video_device_release(vfd);
	return ret;
}