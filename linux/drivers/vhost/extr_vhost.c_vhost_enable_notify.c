#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vhost_virtqueue {int used_flags; scalar_t__ avail_idx; TYPE_2__* avail; TYPE_1__* used; } ;
struct vhost_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio16 ;
struct TYPE_4__ {int /*<<< orphan*/  idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_RING_F_EVENT_IDX ; 
 int VRING_USED_F_NO_NOTIFY ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ vhost16_to_cpu (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vhost_avail_event (struct vhost_virtqueue*) ; 
 int vhost_get_avail_idx (struct vhost_virtqueue*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_has_feature (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int vhost_update_avail_event (struct vhost_virtqueue*,scalar_t__) ; 
 int vhost_update_used_flags (struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,int /*<<< orphan*/ *,int) ; 

bool vhost_enable_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
{
	__virtio16 avail_idx;
	int r;

	if (!(vq->used_flags & VRING_USED_F_NO_NOTIFY))
		return false;
	vq->used_flags &= ~VRING_USED_F_NO_NOTIFY;
	if (!vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX)) {
		r = vhost_update_used_flags(vq);
		if (r) {
			vq_err(vq, "Failed to enable notification at %p: %d\n",
			       &vq->used->flags, r);
			return false;
		}
	} else {
		r = vhost_update_avail_event(vq, vq->avail_idx);
		if (r) {
			vq_err(vq, "Failed to update avail event index at %p: %d\n",
			       vhost_avail_event(vq), r);
			return false;
		}
	}
	/* They could have slipped one in as we were doing that: make
	 * sure it's written, then check again. */
	smp_mb();
	r = vhost_get_avail_idx(vq, &avail_idx);
	if (r) {
		vq_err(vq, "Failed to check avail idx at %p: %d\n",
		       &vq->avail->idx, r);
		return false;
	}

	return vhost16_to_cpu(vq, avail_idx) != vq->avail_idx;
}