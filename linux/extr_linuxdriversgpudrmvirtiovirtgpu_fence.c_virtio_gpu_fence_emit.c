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
struct virtio_gpu_fence_driver {int /*<<< orphan*/  lock; int /*<<< orphan*/  fences; int /*<<< orphan*/  context; scalar_t__ sync_seq; } ;
struct virtio_gpu_fence {scalar_t__ seq; int /*<<< orphan*/  node; int /*<<< orphan*/  f; struct virtio_gpu_fence_driver* drv; } ;
struct virtio_gpu_device {struct virtio_gpu_fence_driver fence_drv; } ;
struct virtio_gpu_ctrl_hdr {int /*<<< orphan*/  fence_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  VIRTIO_GPU_FLAG_FENCE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct virtio_gpu_fence* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virtio_fence_ops ; 

int virtio_gpu_fence_emit(struct virtio_gpu_device *vgdev,
			  struct virtio_gpu_ctrl_hdr *cmd_hdr,
			  struct virtio_gpu_fence **fence)
{
	struct virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	unsigned long irq_flags;

	*fence = kmalloc(sizeof(struct virtio_gpu_fence), GFP_ATOMIC);
	if ((*fence) == NULL)
		return -ENOMEM;

	spin_lock_irqsave(&drv->lock, irq_flags);
	(*fence)->drv = drv;
	(*fence)->seq = ++drv->sync_seq;
	dma_fence_init(&(*fence)->f, &virtio_fence_ops, &drv->lock,
		       drv->context, (*fence)->seq);
	dma_fence_get(&(*fence)->f);
	list_add_tail(&(*fence)->node, &drv->fences);
	spin_unlock_irqrestore(&drv->lock, irq_flags);

	cmd_hdr->flags |= cpu_to_le32(VIRTIO_GPU_FLAG_FENCE);
	cmd_hdr->fence_id = cpu_to_le64((*fence)->seq);
	return 0;
}