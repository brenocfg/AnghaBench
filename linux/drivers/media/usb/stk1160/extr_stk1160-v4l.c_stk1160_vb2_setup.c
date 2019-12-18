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
struct vb2_queue {int io_modes; int buf_struct_size; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct stk1160* drv_priv; int /*<<< orphan*/  type; } ;
struct stk1160_buffer {int dummy; } ;
struct stk1160 {int /*<<< orphan*/  avail_bufs; int /*<<< orphan*/  vb_queue_lock; struct vb2_queue vb_vidq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  stk1160_video_qops ; 
 int vb2_queue_init (struct vb2_queue*) ; 
 int /*<<< orphan*/  vb2_vmalloc_memops ; 

int stk1160_vb2_setup(struct stk1160 *dev)
{
	int rc;
	struct vb2_queue *q;

	q = &dev->vb_vidq;
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_READ | VB2_MMAP | VB2_USERPTR | VB2_DMABUF;
	q->drv_priv = dev;
	q->buf_struct_size = sizeof(struct stk1160_buffer);
	q->ops = &stk1160_video_qops;
	q->mem_ops = &vb2_vmalloc_memops;
	q->lock = &dev->vb_queue_lock;
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	rc = vb2_queue_init(q);
	if (rc < 0)
		return rc;

	/* initialize video dma queue */
	INIT_LIST_HEAD(&dev->avail_bufs);

	return 0;
}