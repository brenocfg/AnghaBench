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
struct vring_virtqueue {scalar_t__ packed_ring; int /*<<< orphan*/  weak_barriers; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int /*<<< orphan*/  virtio_mb (int /*<<< orphan*/ ) ; 
 int virtqueue_poll_packed (struct virtqueue*,unsigned int) ; 
 int virtqueue_poll_split (struct virtqueue*,unsigned int) ; 

bool virtqueue_poll(struct virtqueue *_vq, unsigned last_used_idx)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	virtio_mb(vq->weak_barriers);
	return vq->packed_ring ? virtqueue_poll_packed(_vq, last_used_idx) :
				 virtqueue_poll_split(_vq, last_used_idx);
}