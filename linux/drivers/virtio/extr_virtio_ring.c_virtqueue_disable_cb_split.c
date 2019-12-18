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
struct TYPE_5__ {TYPE_1__* avail; } ;
struct TYPE_6__ {int avail_flags_shadow; TYPE_2__ vring; } ;
struct vring_virtqueue {TYPE_3__ split; int /*<<< orphan*/  event; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int VRING_AVAIL_F_NO_INTERRUPT ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

__attribute__((used)) static void virtqueue_disable_cb_split(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	if (!(vq->split.avail_flags_shadow & VRING_AVAIL_F_NO_INTERRUPT)) {
		vq->split.avail_flags_shadow |= VRING_AVAIL_F_NO_INTERRUPT;
		if (!vq->event)
			vq->split.vring.avail->flags =
				cpu_to_virtio16(_vq->vdev,
						vq->split.avail_flags_shadow);
	}
}