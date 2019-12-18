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
 void* virtqueue_get_buf_ctx_packed (struct virtqueue*,unsigned int*,void**) ; 
 void* virtqueue_get_buf_ctx_split (struct virtqueue*,unsigned int*,void**) ; 

void *virtqueue_get_buf_ctx(struct virtqueue *_vq, unsigned int *len,
			    void **ctx)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	return vq->packed_ring ? virtqueue_get_buf_ctx_packed(_vq, len, ctx) :
				 virtqueue_get_buf_ctx_split(_vq, len, ctx);
}