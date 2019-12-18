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
struct virtio_gpu_fence_driver {int /*<<< orphan*/  context; int /*<<< orphan*/  lock; } ;
struct virtio_gpu_fence {int /*<<< orphan*/  f; struct virtio_gpu_fence_driver* drv; } ;
struct virtio_gpu_device {struct virtio_gpu_fence_driver fence_drv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_fence_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct virtio_gpu_fence* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_fence_ops ; 

struct virtio_gpu_fence *virtio_gpu_fence_alloc(struct virtio_gpu_device *vgdev)
{
	struct virtio_gpu_fence_driver *drv = &vgdev->fence_drv;
	struct virtio_gpu_fence *fence = kzalloc(sizeof(struct virtio_gpu_fence),
							GFP_KERNEL);
	if (!fence)
		return fence;

	fence->drv = drv;

	/* This only partially initializes the fence because the seqno is
	 * unknown yet.  The fence must not be used outside of the driver
	 * until virtio_gpu_fence_emit is called.
	 */
	dma_fence_init(&fence->f, &virtio_fence_ops, &drv->lock, drv->context, 0);

	return fence;
}