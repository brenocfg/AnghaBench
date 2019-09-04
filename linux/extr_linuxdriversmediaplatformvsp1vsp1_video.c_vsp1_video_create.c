#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* queue; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  release; int /*<<< orphan*/  vfl_type; int /*<<< orphan*/  name; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  entity; int /*<<< orphan*/  vfl_dir; } ;
struct TYPE_11__ {int io_modes; int buf_struct_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct vsp1_video* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
struct vsp1_video {struct vsp1_device* vsp1; TYPE_3__ video; TYPE_5__ queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; TYPE_6__ pad; int /*<<< orphan*/  irqqueue; int /*<<< orphan*/  irqlock; struct vsp1_rwpf* rwpf; } ;
struct vsp1_vb2_buffer {int dummy; } ;
struct TYPE_8__ {char* name; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ subdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixelformat; } ;
struct vsp1_rwpf {TYPE_2__ entity; int /*<<< orphan*/  fmtinfo; TYPE_7__ format; struct vsp1_video* video; } ;
struct vsp1_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_master; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vsp1_video* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_COPY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int /*<<< orphan*/  VFL_DIR_TX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 scalar_t__ VSP1_ENTITY_RPF ; 
 int /*<<< orphan*/  VSP1_VIDEO_DEF_FORMAT ; 
 int /*<<< orphan*/  VSP1_VIDEO_DEF_HEIGHT ; 
 int /*<<< orphan*/  VSP1_VIDEO_DEF_WIDTH ; 
 int /*<<< orphan*/  __vsp1_video_try_format (struct vsp1_video*,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct vsp1_video* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (TYPE_5__*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct vsp1_video*) ; 
 int /*<<< orphan*/  vsp1_video_cleanup (struct vsp1_video*) ; 
 int /*<<< orphan*/  vsp1_video_fops ; 
 int /*<<< orphan*/  vsp1_video_ioctl_ops ; 
 int /*<<< orphan*/  vsp1_video_queue_qops ; 

struct vsp1_video *vsp1_video_create(struct vsp1_device *vsp1,
				     struct vsp1_rwpf *rwpf)
{
	struct vsp1_video *video;
	const char *direction;
	int ret;

	video = devm_kzalloc(vsp1->dev, sizeof(*video), GFP_KERNEL);
	if (!video)
		return ERR_PTR(-ENOMEM);

	rwpf->video = video;

	video->vsp1 = vsp1;
	video->rwpf = rwpf;

	if (rwpf->entity.type == VSP1_ENTITY_RPF) {
		direction = "input";
		video->type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
		video->pad.flags = MEDIA_PAD_FL_SOURCE;
		video->video.vfl_dir = VFL_DIR_TX;
	} else {
		direction = "output";
		video->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
		video->pad.flags = MEDIA_PAD_FL_SINK;
		video->video.vfl_dir = VFL_DIR_RX;
	}

	mutex_init(&video->lock);
	spin_lock_init(&video->irqlock);
	INIT_LIST_HEAD(&video->irqqueue);

	/* Initialize the media entity... */
	ret = media_entity_pads_init(&video->video.entity, 1, &video->pad);
	if (ret < 0)
		return ERR_PTR(ret);

	/* ... and the format ... */
	rwpf->format.pixelformat = VSP1_VIDEO_DEF_FORMAT;
	rwpf->format.width = VSP1_VIDEO_DEF_WIDTH;
	rwpf->format.height = VSP1_VIDEO_DEF_HEIGHT;
	__vsp1_video_try_format(video, &rwpf->format, &rwpf->fmtinfo);

	/* ... and the video node... */
	video->video.v4l2_dev = &video->vsp1->v4l2_dev;
	video->video.fops = &vsp1_video_fops;
	snprintf(video->video.name, sizeof(video->video.name), "%s %s",
		 rwpf->entity.subdev.name, direction);
	video->video.vfl_type = VFL_TYPE_GRABBER;
	video->video.release = video_device_release_empty;
	video->video.ioctl_ops = &vsp1_video_ioctl_ops;

	video_set_drvdata(&video->video, video);

	video->queue.type = video->type;
	video->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	video->queue.lock = &video->lock;
	video->queue.drv_priv = video;
	video->queue.buf_struct_size = sizeof(struct vsp1_vb2_buffer);
	video->queue.ops = &vsp1_video_queue_qops;
	video->queue.mem_ops = &vb2_dma_contig_memops;
	video->queue.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	video->queue.dev = video->vsp1->bus_master;
	ret = vb2_queue_init(&video->queue);
	if (ret < 0) {
		dev_err(video->vsp1->dev, "failed to initialize vb2 queue\n");
		goto error;
	}

	/* ... and register the video device. */
	video->video.queue = &video->queue;
	ret = video_register_device(&video->video, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		dev_err(video->vsp1->dev, "failed to register video device\n");
		goto error;
	}

	return video;

error:
	vsp1_video_cleanup(video);
	return ERR_PTR(ret);
}