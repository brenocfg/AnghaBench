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
typedef  int u16 ;
struct TYPE_7__ {int num; TYPE_2__* driver; } ;
struct TYPE_8__ {int used_wrap_counter; int event_flags_shadow; TYPE_3__ vring; } ;
struct TYPE_5__ {int num_free; } ;
struct vring_virtqueue {int last_used_idx; TYPE_4__ packed; int /*<<< orphan*/  weak_barriers; scalar_t__ event; TYPE_1__ vq; } ;
struct virtqueue {int dummy; } ;
struct TYPE_6__ {void* flags; void* off_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int VRING_PACKED_EVENT_FLAG_DESC ; 
 int VRING_PACKED_EVENT_FLAG_DISABLE ; 
 int VRING_PACKED_EVENT_FLAG_ENABLE ; 
 int VRING_PACKED_EVENT_F_WRAP_CTR ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ is_used_desc_packed (struct vring_virtqueue*,int,int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int /*<<< orphan*/  virtio_mb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_wmb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool virtqueue_enable_cb_delayed_packed(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	u16 used_idx, wrap_counter;
	u16 bufs;

	START_USE(vq);

	/*
	 * We optimistically turn back on interrupts, then check if there was
	 * more to do.
	 */

	if (vq->event) {
		/* TODO: tune this threshold */
		bufs = (vq->packed.vring.num - vq->vq.num_free) * 3 / 4;
		wrap_counter = vq->packed.used_wrap_counter;

		used_idx = vq->last_used_idx + bufs;
		if (used_idx >= vq->packed.vring.num) {
			used_idx -= vq->packed.vring.num;
			wrap_counter ^= 1;
		}

		vq->packed.vring.driver->off_wrap = cpu_to_le16(used_idx |
			(wrap_counter << VRING_PACKED_EVENT_F_WRAP_CTR));

		/*
		 * We need to update event offset and event wrap
		 * counter first before updating event flags.
		 */
		virtio_wmb(vq->weak_barriers);
	}

	if (vq->packed.event_flags_shadow == VRING_PACKED_EVENT_FLAG_DISABLE) {
		vq->packed.event_flags_shadow = vq->event ?
				VRING_PACKED_EVENT_FLAG_DESC :
				VRING_PACKED_EVENT_FLAG_ENABLE;
		vq->packed.vring.driver->flags =
				cpu_to_le16(vq->packed.event_flags_shadow);
	}

	/*
	 * We need to update event suppression structure first
	 * before re-checking for more used buffers.
	 */
	virtio_mb(vq->weak_barriers);

	if (is_used_desc_packed(vq,
				vq->last_used_idx,
				vq->packed.used_wrap_counter)) {
		END_USE(vq);
		return false;
	}

	END_USE(vq);
	return true;
}