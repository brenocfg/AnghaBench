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
struct virtqueue {int /*<<< orphan*/  index; int /*<<< orphan*/  vdev; } ;
struct virtio_mmio_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ VIRTIO_MMIO_QUEUE_NOTIFY ; 
 struct virtio_mmio_device* to_virtio_mmio_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool vm_notify(struct virtqueue *vq)
{
	struct virtio_mmio_device *vm_dev = to_virtio_mmio_device(vq->vdev);

	/* We write the queue's selector into the notification register to
	 * signal the other end */
	writel(vq->index, vm_dev->base + VIRTIO_MMIO_QUEUE_NOTIFY);
	return true;
}