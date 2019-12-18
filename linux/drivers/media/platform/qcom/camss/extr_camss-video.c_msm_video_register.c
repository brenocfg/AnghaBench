#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct video_device {int device_caps; int /*<<< orphan*/  entity; int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; struct vb2_queue* queue; int /*<<< orphan*/  vfl_dir; struct v4l2_device* v4l2_dev; int /*<<< orphan*/  release; int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct vb2_queue {int io_modes; int buf_struct_size; int /*<<< orphan*/ * lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * mem_ops; struct camss_video* drv_priv; } ;
struct v4l2_device {int /*<<< orphan*/  dev; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;
struct camss_video {int /*<<< orphan*/  q_lock; struct vb2_queue vb2_q; int /*<<< orphan*/  lock; TYPE_1__* camss; void* nformats; void* formats; struct video_device vdev; struct media_pad pad; } ;
struct camss_buffer {int dummy; } ;
struct TYPE_2__ {scalar_t__ version; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ CAMSS_8x16 ; 
 scalar_t__ CAMSS_8x96 ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE_MPLANE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int /*<<< orphan*/  VFL_DIR_RX ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* formats_pix_8x16 ; 
 void* formats_pix_8x96 ; 
 void* formats_rdi_8x16 ; 
 void* formats_rdi_8x96 ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,struct media_pad*) ; 
 int /*<<< orphan*/  msm_vid_fops ; 
 int /*<<< orphan*/  msm_vid_ioctl_ops ; 
 int msm_video_init_format (struct camss_video*) ; 
 int /*<<< orphan*/  msm_video_release ; 
 int /*<<< orphan*/  msm_video_vb2_q_ops ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  vb2_dma_sg_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_queue_release (struct vb2_queue*) ; 
 int video_register_device (struct video_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct camss_video*) ; 

int msm_video_register(struct camss_video *video, struct v4l2_device *v4l2_dev,
		       const char *name, int is_pix)
{
	struct media_pad *pad = &video->pad;
	struct video_device *vdev;
	struct vb2_queue *q;
	int ret;

	vdev = &video->vdev;

	mutex_init(&video->q_lock);

	q = &video->vb2_q;
	q->drv_priv = video;
	q->mem_ops = &vb2_dma_sg_memops;
	q->ops = &msm_video_vb2_q_ops;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	q->io_modes = VB2_DMABUF | VB2_MMAP | VB2_READ;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->buf_struct_size = sizeof(struct camss_buffer);
	q->dev = video->camss->dev;
	q->lock = &video->q_lock;
	ret = vb2_queue_init(q);
	if (ret < 0) {
		dev_err(v4l2_dev->dev, "Failed to init vb2 queue: %d\n", ret);
		goto error_vb2_init;
	}

	pad->flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vdev->entity, 1, pad);
	if (ret < 0) {
		dev_err(v4l2_dev->dev, "Failed to init video entity: %d\n",
			ret);
		goto error_media_init;
	}

	mutex_init(&video->lock);

	if (video->camss->version == CAMSS_8x16) {
		if (is_pix) {
			video->formats = formats_pix_8x16;
			video->nformats = ARRAY_SIZE(formats_pix_8x16);
		} else {
			video->formats = formats_rdi_8x16;
			video->nformats = ARRAY_SIZE(formats_rdi_8x16);
		}
	} else if (video->camss->version == CAMSS_8x96) {
		if (is_pix) {
			video->formats = formats_pix_8x96;
			video->nformats = ARRAY_SIZE(formats_pix_8x96);
		} else {
			video->formats = formats_rdi_8x96;
			video->nformats = ARRAY_SIZE(formats_rdi_8x96);
		}
	} else {
		goto error_video_register;
	}

	ret = msm_video_init_format(video);
	if (ret < 0) {
		dev_err(v4l2_dev->dev, "Failed to init format: %d\n", ret);
		goto error_video_register;
	}

	vdev->fops = &msm_vid_fops;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING |
							V4L2_CAP_READWRITE;
	vdev->ioctl_ops = &msm_vid_ioctl_ops;
	vdev->release = msm_video_release;
	vdev->v4l2_dev = v4l2_dev;
	vdev->vfl_dir = VFL_DIR_RX;
	vdev->queue = &video->vb2_q;
	vdev->lock = &video->lock;
	strscpy(vdev->name, name, sizeof(vdev->name));

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		dev_err(v4l2_dev->dev, "Failed to register video device: %d\n",
			ret);
		goto error_video_register;
	}

	video_set_drvdata(vdev, video);
	atomic_inc(&video->camss->ref_count);

	return 0;

error_video_register:
	media_entity_cleanup(&vdev->entity);
	mutex_destroy(&video->lock);
error_media_init:
	vb2_queue_release(&video->vb2_q);
error_vb2_init:
	mutex_destroy(&video->q_lock);

	return ret;
}