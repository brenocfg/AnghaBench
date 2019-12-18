#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vsp1_histogram_buffer {int dummy; } ;
struct TYPE_9__ {int device_caps; TYPE_5__* queue; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/  release; int /*<<< orphan*/  vfl_type; int /*<<< orphan*/  name; int /*<<< orphan*/ * fops; int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  entity; int /*<<< orphan*/  vfl_dir; } ;
struct TYPE_10__ {int io_modes; int buf_struct_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct vsp1_histogram* drv_priv; int /*<<< orphan*/ * lock; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_8__ {int type; TYPE_1__ subdev; struct vsp1_entity_operations const* ops; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; } ;
struct vsp1_histogram {unsigned int const* formats; unsigned int num_formats; size_t data_size; TYPE_3__ video; TYPE_5__ queue; int /*<<< orphan*/  lock; TYPE_2__ entity; TYPE_6__ pad; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  irqqueue; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  meta_format; } ;
struct vsp1_entity_operations {int dummy; } ;
struct vsp1_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  v4l2_dev; } ;
typedef  enum vsp1_entity_type { ____Placeholder_vsp1_entity_type } vsp1_entity_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_STATISTICS ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_COPY ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_META_CAPTURE ; 
 int V4L2_CAP_META_CAPTURE ; 
 int V4L2_CAP_STREAMING ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  histo_ops ; 
 int /*<<< orphan*/  histo_v4l2_fops ; 
 int /*<<< orphan*/  histo_v4l2_ioctl_ops ; 
 int /*<<< orphan*/  histo_video_queue_qops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_6__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int vb2_queue_init (TYPE_5__*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 
 int /*<<< orphan*/  video_device_release_empty ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct vsp1_histogram*) ; 
 int vsp1_entity_init (struct vsp1_device*,TYPE_2__*,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_histogram_cleanup (struct vsp1_histogram*) ; 

int vsp1_histogram_init(struct vsp1_device *vsp1, struct vsp1_histogram *histo,
			enum vsp1_entity_type type, const char *name,
			const struct vsp1_entity_operations *ops,
			const unsigned int *formats, unsigned int num_formats,
			size_t data_size, u32 meta_format)
{
	int ret;

	histo->formats = formats;
	histo->num_formats = num_formats;
	histo->data_size = data_size;
	histo->meta_format = meta_format;

	histo->pad.flags = MEDIA_PAD_FL_SINK;
	histo->video.vfl_dir = VFL_DIR_RX;

	mutex_init(&histo->lock);
	spin_lock_init(&histo->irqlock);
	INIT_LIST_HEAD(&histo->irqqueue);
	init_waitqueue_head(&histo->wait_queue);

	/* Initialize the VSP entity... */
	histo->entity.ops = ops;
	histo->entity.type = type;

	ret = vsp1_entity_init(vsp1, &histo->entity, name, 2, &histo_ops,
			       MEDIA_ENT_F_PROC_VIDEO_STATISTICS);
	if (ret < 0)
		return ret;

	/* ... and the media entity... */
	ret = media_entity_pads_init(&histo->video.entity, 1, &histo->pad);
	if (ret < 0)
		return ret;

	/* ... and the video node... */
	histo->video.v4l2_dev = &vsp1->v4l2_dev;
	histo->video.fops = &histo_v4l2_fops;
	snprintf(histo->video.name, sizeof(histo->video.name),
		 "%s histo", histo->entity.subdev.name);
	histo->video.vfl_type = VFL_TYPE_GRABBER;
	histo->video.release = video_device_release_empty;
	histo->video.ioctl_ops = &histo_v4l2_ioctl_ops;
	histo->video.device_caps = V4L2_CAP_META_CAPTURE | V4L2_CAP_STREAMING;

	video_set_drvdata(&histo->video, histo);

	/* ... and the buffers queue... */
	histo->queue.type = V4L2_BUF_TYPE_META_CAPTURE;
	histo->queue.io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	histo->queue.lock = &histo->lock;
	histo->queue.drv_priv = histo;
	histo->queue.buf_struct_size = sizeof(struct vsp1_histogram_buffer);
	histo->queue.ops = &histo_video_queue_qops;
	histo->queue.mem_ops = &vb2_vmalloc_memops;
	histo->queue.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_COPY;
	histo->queue.dev = vsp1->dev;
	ret = vb2_queue_init(&histo->queue);
	if (ret < 0) {
		dev_err(vsp1->dev, "failed to initialize vb2 queue\n");
		goto error;
	}

	/* ... and register the video device. */
	histo->video.queue = &histo->queue;
	ret = video_register_device(&histo->video, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		dev_err(vsp1->dev, "failed to register video device\n");
		goto error;
	}

	return 0;

error:
	vsp1_histogram_cleanup(histo);
	return ret;
}