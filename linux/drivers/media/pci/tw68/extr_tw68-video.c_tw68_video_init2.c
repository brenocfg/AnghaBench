#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* queue; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_8__ {int io_modes; int gfp_flags; int buf_struct_size; int min_buffers_needed; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * lock; struct tw68_dev* drv_priv; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/  type; } ;
struct tw68_dev {int width; int height; TYPE_2__ vdev; TYPE_4__ vidq; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; TYPE_1__* pci; int /*<<< orphan*/  active; int /*<<< orphan*/  field; int /*<<< orphan*/  fmt; } ;
struct tw68_buf {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_BGR24 ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int __GFP_DMA32 ; 
 int __GFP_KSWAPD_RECLAIM ; 
 int /*<<< orphan*/  format_by_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tvnorm (struct tw68_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvnorms ; 
 int /*<<< orphan*/  tw68_video_qops ; 
 TYPE_2__ tw68_video_template ; 
 int /*<<< orphan*/  vb2_dma_sg_memops ; 
 int vb2_queue_init (TYPE_4__*) ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct tw68_dev*) ; 

int tw68_video_init2(struct tw68_dev *dev, int video_nr)
{
	int ret;

	set_tvnorm(dev, &tvnorms[0]);

	dev->fmt      = format_by_fourcc(V4L2_PIX_FMT_BGR24);
	dev->width    = 720;
	dev->height   = 576;
	dev->field    = V4L2_FIELD_INTERLACED;

	INIT_LIST_HEAD(&dev->active);
	dev->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	dev->vidq.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	dev->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ | VB2_DMABUF;
	dev->vidq.ops = &tw68_video_qops;
	dev->vidq.mem_ops = &vb2_dma_sg_memops;
	dev->vidq.drv_priv = dev;
	dev->vidq.gfp_flags = __GFP_DMA32 | __GFP_KSWAPD_RECLAIM;
	dev->vidq.buf_struct_size = sizeof(struct tw68_buf);
	dev->vidq.lock = &dev->lock;
	dev->vidq.min_buffers_needed = 2;
	dev->vidq.dev = &dev->pci->dev;
	ret = vb2_queue_init(&dev->vidq);
	if (ret)
		return ret;
	dev->vdev = tw68_video_template;
	dev->vdev.v4l2_dev = &dev->v4l2_dev;
	dev->vdev.lock = &dev->lock;
	dev->vdev.queue = &dev->vidq;
	video_set_drvdata(&dev->vdev, dev);
	return video_register_device(&dev->vdev, VFL_TYPE_GRABBER, video_nr);
}