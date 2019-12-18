#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ desc; scalar_t__ used; } ;
struct TYPE_6__ {TYPE_2__ vring; scalar_t__ queue_dma_addr; } ;
struct TYPE_4__ {scalar_t__ device_event_dma_addr; } ;
struct vring_virtqueue {TYPE_3__ split; TYPE_1__ packed; scalar_t__ packed_ring; int /*<<< orphan*/  we_own_ring; } ;
struct virtqueue {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

dma_addr_t virtqueue_get_used_addr(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	BUG_ON(!vq->we_own_ring);

	if (vq->packed_ring)
		return vq->packed.device_event_dma_addr;

	return vq->split.queue_dma_addr +
		((char *)vq->split.vring.used - (char *)vq->split.vring.desc);
}