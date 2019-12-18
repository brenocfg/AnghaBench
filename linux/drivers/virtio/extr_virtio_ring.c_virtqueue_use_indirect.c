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
struct TYPE_2__ {scalar_t__ num_free; } ;
struct vring_virtqueue {TYPE_1__ vq; scalar_t__ indirect; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

__attribute__((used)) static inline bool virtqueue_use_indirect(struct virtqueue *_vq,
					  unsigned int total_sg)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	/*
	 * If the host supports indirect descriptor tables, and we have multiple
	 * buffers, then go indirect. FIXME: tune this threshold
	 */
	return (vq->indirect && total_sg > 1 && vq->vq.num_free);
}