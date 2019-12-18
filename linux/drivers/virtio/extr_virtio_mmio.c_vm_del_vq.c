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
struct virtqueue {unsigned int index; struct virtio_mmio_vq_info* priv; int /*<<< orphan*/  vdev; } ;
struct virtio_mmio_vq_info {int /*<<< orphan*/  node; } ;
struct virtio_mmio_device {int version; scalar_t__ base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_MMIO_QUEUE_PFN ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_READY ; 
 scalar_t__ VIRTIO_MMIO_QUEUE_SEL ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct virtio_mmio_vq_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct virtio_mmio_device* to_virtio_mmio_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void vm_del_vq(struct virtqueue *vq)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vq->vdev);
	struct virtio_mmio_vq_info *info = vq->priv;
	unsigned long flags;
	unsigned int index = vq->index;

	spin_lock_irqsave(&vm_dev->lock, flags);
	list_del(&info->node);
	spin_unlock_irqrestore(&vm_dev->lock, flags);

	/* Select and deactivate the queue */
	writel(index, vm_dev->base + VIRTIO_MMIO_QUEUE_SEL);
	if (vm_dev->version == 1) {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_PFN);
	} else {
		writel(0, vm_dev->base + VIRTIO_MMIO_QUEUE_READY);
		WARN_ON(readl(vm_dev->base + VIRTIO_MMIO_QUEUE_READY));
	}

	vring_del_virtqueue(vq);

	kfree(info);
}