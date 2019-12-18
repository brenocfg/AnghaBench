#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_gpu_fence_driver {int /*<<< orphan*/  lock; int /*<<< orphan*/  fences; scalar_t__ sync_seq; } ;
struct TYPE_3__ {scalar_t__ seqno; } ;
struct virtio_gpu_fence {TYPE_1__ f; int /*<<< orphan*/  node; } ;
struct virtio_gpu_device {struct virtio_gpu_fence_driver fence_drv; } ;
struct virtio_gpu_ctrl_hdr {int /*<<< orphan*/  fence_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_GPU_FLAG_FENCE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_get (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_dma_fence_emit (TYPE_1__*) ; 

void virtio_gpu_fence_emit(struct virtio_gpu_device *vgdev,
			  struct virtio_gpu_ctrl_hdr *cmd_hdr,
			  struct virtio_gpu_fence *fence)
{
	struct virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	unsigned long irq_flags;

	spin_lock_irqsave(&drv->lock, irq_flags);
	fence->f.seqno = ++drv->sync_seq;
	dma_fence_get(&fence->f);
	list_add_tail(&fence->node, &drv->fences);
	spin_unlock_irqrestore(&drv->lock, irq_flags);

	trace_dma_fence_emit(&fence->f);

	cmd_hdr->flags |= cpu_to_le32(VIRTIO_GPU_FLAG_FENCE);
	cmd_hdr->fence_id = cpu_to_le64(fence->f.seqno);
}