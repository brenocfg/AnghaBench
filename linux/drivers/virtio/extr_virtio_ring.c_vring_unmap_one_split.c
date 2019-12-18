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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vdev; } ;
struct vring_virtqueue {TYPE_1__ vq; int /*<<< orphan*/  use_dma_api; } ;
struct vring_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int VRING_DESC_F_INDIRECT ; 
 int VRING_DESC_F_WRITE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio64_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_dma_dev (struct vring_virtqueue const*) ; 

__attribute__((used)) static void vring_unmap_one_split(const struct vring_virtqueue *vq,
				  struct vring_desc *desc)
{
	u16 flags;

	if (!vq->use_dma_api)
		return;

	flags = virtio16_to_cpu(vq->vq.vdev, desc->flags);

	if (flags & VRING_DESC_F_INDIRECT) {
		dma_unmap_single(vring_dma_dev(vq),
				 virtio64_to_cpu(vq->vq.vdev, desc->addr),
				 virtio32_to_cpu(vq->vq.vdev, desc->len),
				 (flags & VRING_DESC_F_WRITE) ?
				 DMA_FROM_DEVICE : DMA_TO_DEVICE);
	} else {
		dma_unmap_page(vring_dma_dev(vq),
			       virtio64_to_cpu(vq->vq.vdev, desc->addr),
			       virtio32_to_cpu(vq->vq.vdev, desc->len),
			       (flags & VRING_DESC_F_WRITE) ?
			       DMA_FROM_DEVICE : DMA_TO_DEVICE);
	}
}