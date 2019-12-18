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
typedef  scalar_t__ u16 ;
struct TYPE_6__ {TYPE_1__* used; } ;
struct TYPE_5__ {TYPE_3__ vring; scalar_t__ avail_idx_shadow; } ;
struct vring_virtqueue {TYPE_2__ split; scalar_t__ event; scalar_t__ num_added; int /*<<< orphan*/  weak_barriers; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  LAST_ADD_TIME_CHECK (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  LAST_ADD_TIME_INVALID (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  VRING_USED_F_NO_NOTIFY ; 
 int cpu_to_virtio16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int /*<<< orphan*/  virtio16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_mb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_avail_event (TYPE_3__*) ; 
 int vring_need_event (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool virtqueue_kick_prepare_split(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	u16 new, old;
	bool needs_kick;

	START_USE(vq);
	/* We need to expose available array entries before checking avail
	 * event. */
	virtio_mb(vq->weak_barriers);

	old = vq->split.avail_idx_shadow - vq->num_added;
	new = vq->split.avail_idx_shadow;
	vq->num_added = 0;

	LAST_ADD_TIME_CHECK(vq);
	LAST_ADD_TIME_INVALID(vq);

	if (vq->event) {
		needs_kick = vring_need_event(virtio16_to_cpu(_vq->vdev,
					vring_avail_event(&vq->split.vring)),
					      new, old);
	} else {
		needs_kick = !(vq->split.vring.used->flags &
					cpu_to_virtio16(_vq->vdev,
						VRING_USED_F_NO_NOTIFY));
	}
	END_USE(vq);
	return needs_kick;
}