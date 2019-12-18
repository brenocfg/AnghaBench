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
struct vring_virtqueue {scalar_t__ packed_ring; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 void* virtqueue_detach_unused_buf_packed (struct virtqueue*) ; 
 void* virtqueue_detach_unused_buf_split (struct virtqueue*) ; 

void *virtqueue_detach_unused_buf(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	return vq->packed_ring ? virtqueue_detach_unused_buf_packed(_vq) :
				 virtqueue_detach_unused_buf_split(_vq);
}