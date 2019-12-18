#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int num; } ;
struct TYPE_7__ {TYPE_4__ vring; TYPE_1__* desc_state; } ;
struct TYPE_6__ {unsigned int num_free; } ;
struct vring_virtqueue {TYPE_3__ packed; TYPE_2__ vq; } ;
struct virtqueue {int dummy; } ;
struct TYPE_5__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  detach_buf_packed (struct vring_virtqueue*,unsigned int,int /*<<< orphan*/ *) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

__attribute__((used)) static void *virtqueue_detach_unused_buf_packed(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	unsigned int i;
	void *buf;

	START_USE(vq);

	for (i = 0; i < vq->packed.vring.num; i++) {
		if (!vq->packed.desc_state[i].data)
			continue;
		/* detach_buf clears data, so grab it now. */
		buf = vq->packed.desc_state[i].data;
		detach_buf_packed(vq, i, NULL);
		END_USE(vq);
		return buf;
	}
	/* That should have freed everything. */
	BUG_ON(vq->vq.num_free != vq->packed.vring.num);

	END_USE(vq);
	return NULL;
}