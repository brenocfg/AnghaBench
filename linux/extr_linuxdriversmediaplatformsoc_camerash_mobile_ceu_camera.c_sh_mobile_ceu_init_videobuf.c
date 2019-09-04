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
struct vb2_queue {int io_modes; int buf_struct_size; int /*<<< orphan*/  dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  timestamp_flags; int /*<<< orphan*/ * mem_ops; int /*<<< orphan*/ * ops; struct soc_camera_device* drv_priv; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct soc_camera_host {TYPE_1__ v4l2_dev; int /*<<< orphan*/  host_lock; } ;
struct soc_camera_device {int /*<<< orphan*/  parent; } ;
struct sh_mobile_ceu_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 
 int /*<<< orphan*/  sh_mobile_ceu_videobuf_ops ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_memops ; 
 int vb2_queue_init (struct vb2_queue*) ; 

__attribute__((used)) static int sh_mobile_ceu_init_videobuf(struct vb2_queue *q,
				       struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);

	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_USERPTR;
	q->drv_priv = icd;
	q->ops = &sh_mobile_ceu_videobuf_ops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->buf_struct_size = sizeof(struct sh_mobile_ceu_buffer);
	q->timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->lock = &ici->host_lock;
	q->dev = ici->v4l2_dev.dev;

	return vb2_queue_init(q);
}