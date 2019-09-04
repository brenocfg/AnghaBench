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
struct vb2_queue {int io_modes; int buf_struct_size; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dev; int /*<<< orphan*/  timestamp_flags; struct pxa_camera_dev* drv_priv; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct pxa_camera_dev {int /*<<< orphan*/  mlock; TYPE_1__ v4l2_dev; struct vb2_queue vb2_vq; } ;
struct pxa_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct vb2_queue*,int) ; 
 int /*<<< orphan*/  memset (struct vb2_queue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 int /*<<< orphan*/  pxac_vb2_ops ; 
 int /*<<< orphan*/  vb2_dma_sg_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 

__attribute__((used)) static int pxa_camera_init_videobuf2(struct pxa_camera_dev *pcdev)
{
	int ret;
	struct vb2_queue *vq = &pcdev->vb2_vq;

	memset(vq, 0, sizeof(*vq));
	vq->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vq->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	vq->drv_priv = pcdev;
	vq->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vq->buf_struct_size = sizeof(struct pxa_buffer);
	vq->dev = pcdev->v4l2_dev.dev;

	vq->ops = &pxac_vb2_ops;
	vq->mem_ops = &vb2_dma_sg_memops;
	vq->lock = &pcdev->mlock;

	ret = vb2_queue_init(vq);
	dev_dbg(pcdev_to_dev(pcdev),
		 "vb2_queue_init(vq=%p): %d\n", vq, ret);

	return ret;
}