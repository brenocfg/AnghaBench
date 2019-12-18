#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_9__ {size_t num; TYPE_3__* driver; TYPE_1__* desc; } ;
struct TYPE_10__ {int used_wrap_counter; scalar_t__ event_flags_shadow; TYPE_4__ vring; TYPE_2__* desc_state; } ;
struct vring_virtqueue {int broken; size_t last_used_idx; TYPE_5__ packed; int /*<<< orphan*/  weak_barriers; } ;
struct virtqueue {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  off_wrap; } ;
struct TYPE_7__ {scalar_t__ num; void* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_RING (struct vring_virtqueue*,char*,size_t) ; 
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  LAST_ADD_TIME_INVALID (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 scalar_t__ VRING_PACKED_EVENT_FLAG_DESC ; 
 int VRING_PACKED_EVENT_F_WRAP_CTR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  detach_buf_packed (struct vring_virtqueue*,size_t,void**) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  more_used_packed (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtio_rmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_store_mb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *virtqueue_get_buf_ctx_packed(struct virtqueue *_vq,
					  unsigned int *len,
					  void **ctx)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	u16 last_used, id;
	void *ret;

	START_USE(vq);

	if (unlikely(vq->broken)) {
		END_USE(vq);
		return NULL;
	}

	if (!more_used_packed(vq)) {
		pr_debug("No more buffers in queue\n");
		END_USE(vq);
		return NULL;
	}

	/* Only get used elements after they have been exposed by host. */
	virtio_rmb(vq->weak_barriers);

	last_used = vq->last_used_idx;
	id = le16_to_cpu(vq->packed.vring.desc[last_used].id);
	*len = le32_to_cpu(vq->packed.vring.desc[last_used].len);

	if (unlikely(id >= vq->packed.vring.num)) {
		BAD_RING(vq, "id %u out of range\n", id);
		return NULL;
	}
	if (unlikely(!vq->packed.desc_state[id].data)) {
		BAD_RING(vq, "id %u is not a head!\n", id);
		return NULL;
	}

	/* detach_buf_packed clears data, so grab it now. */
	ret = vq->packed.desc_state[id].data;
	detach_buf_packed(vq, id, ctx);

	vq->last_used_idx += vq->packed.desc_state[id].num;
	if (unlikely(vq->last_used_idx >= vq->packed.vring.num)) {
		vq->last_used_idx -= vq->packed.vring.num;
		vq->packed.used_wrap_counter ^= 1;
	}

	/*
	 * If we expect an interrupt for the next entry, tell host
	 * by writing event index and flush out the write before
	 * the read in the next get_buf call.
	 */
	if (vq->packed.event_flags_shadow == VRING_PACKED_EVENT_FLAG_DESC)
		virtio_store_mb(vq->weak_barriers,
				&vq->packed.vring.driver->off_wrap,
				cpu_to_le16(vq->last_used_idx |
					(vq->packed.used_wrap_counter <<
					 VRING_PACKED_EVENT_F_WRAP_CTR)));

	LAST_ADD_TIME_INVALID(vq);

	END_USE(vq);
	return ret;
}