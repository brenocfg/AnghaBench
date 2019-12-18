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
struct scatterlist {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int virtqueue_add_packed (struct virtqueue*,struct scatterlist**,unsigned int,unsigned int,unsigned int,void*,void*,int /*<<< orphan*/ ) ; 
 int virtqueue_add_split (struct virtqueue*,struct scatterlist**,unsigned int,unsigned int,unsigned int,void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int virtqueue_add(struct virtqueue *_vq,
				struct scatterlist *sgs[],
				unsigned int total_sg,
				unsigned int out_sgs,
				unsigned int in_sgs,
				void *data,
				void *ctx,
				gfp_t gfp)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	return vq->packed_ring ? virtqueue_add_packed(_vq, sgs, total_sg,
					out_sgs, in_sgs, data, ctx, gfp) :
				 virtqueue_add_split(_vq, sgs, total_sg,
					out_sgs, in_sgs, data, ctx, gfp);
}