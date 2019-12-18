#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vip_buffer {int dummy; } ;
struct vb2_queue {int dummy; } ;
struct TYPE_5__ {int io_modes; int buf_struct_size; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * dev; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct sta2x11_vip* drv_priv; int /*<<< orphan*/  type; } ;
struct sta2x11_vip {int /*<<< orphan*/  lock; int /*<<< orphan*/  buffer_list; TYPE_2__ vb_vidq; int /*<<< orphan*/  v4l_lock; TYPE_1__* pdev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VB2_MMAP ; 
 int VB2_READ ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (TYPE_2__*) ; 
 int /*<<< orphan*/  vip_video_qops ; 

__attribute__((used)) static int sta2x11_vip_init_buffer(struct sta2x11_vip *vip)
{
	int err;

	err = dma_set_coherent_mask(&vip->pdev->dev, DMA_BIT_MASK(29));
	if (err) {
		v4l2_err(&vip->v4l2_dev, "Cannot configure coherent mask");
		return err;
	}
	memset(&vip->vb_vidq, 0, sizeof(struct vb2_queue));
	vip->vb_vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vip->vb_vidq.io_modes = VB2_MMAP | VB2_READ;
	vip->vb_vidq.drv_priv = vip;
	vip->vb_vidq.buf_struct_size = sizeof(struct vip_buffer);
	vip->vb_vidq.ops = &vip_video_qops;
	vip->vb_vidq.mem_ops = &vb2_dma_contig_memops;
	vip->vb_vidq.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	vip->vb_vidq.dev = &vip->pdev->dev;
	vip->vb_vidq.lock = &vip->v4l_lock;
	err = vb2_queue_init(&vip->vb_vidq);
	if (err)
		return err;
	INIT_LIST_HEAD(&vip->buffer_list);
	spin_lock_init(&vip->lock);
	return 0;
}