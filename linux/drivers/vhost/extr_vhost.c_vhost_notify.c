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
struct vhost_virtqueue {scalar_t__ avail_idx; scalar_t__ last_avail_idx; int signalled_used_valid; int /*<<< orphan*/  last_used_idx; int /*<<< orphan*/  signalled_used; } ;
struct vhost_dev {int dummy; } ;
typedef  int __virtio16 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_F_NOTIFY_ON_EMPTY ; 
 int /*<<< orphan*/  VIRTIO_RING_F_EVENT_IDX ; 
 int /*<<< orphan*/  VRING_AVAIL_F_NO_INTERRUPT ; 
 int cpu_to_vhost16 (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost16_to_cpu (struct vhost_virtqueue*,int) ; 
 scalar_t__ vhost_get_avail_flags (struct vhost_virtqueue*,int*) ; 
 scalar_t__ vhost_get_used_event (struct vhost_virtqueue*,int*) ; 
 scalar_t__ vhost_has_feature (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*) ; 
 int vring_need_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vhost_notify(struct vhost_dev *dev, struct vhost_virtqueue *vq)
{
	__u16 old, new;
	__virtio16 event;
	bool v;
	/* Flush out used index updates. This is paired
	 * with the barrier that the Guest executes when enabling
	 * interrupts. */
	smp_mb();

	if (vhost_has_feature(vq, VIRTIO_F_NOTIFY_ON_EMPTY) &&
	    unlikely(vq->avail_idx == vq->last_avail_idx))
		return true;

	if (!vhost_has_feature(vq, VIRTIO_RING_F_EVENT_IDX)) {
		__virtio16 flags;
		if (vhost_get_avail_flags(vq, &flags)) {
			vq_err(vq, "Failed to get flags");
			return true;
		}
		return !(flags & cpu_to_vhost16(vq, VRING_AVAIL_F_NO_INTERRUPT));
	}
	old = vq->signalled_used;
	v = vq->signalled_used_valid;
	new = vq->signalled_used = vq->last_used_idx;
	vq->signalled_used_valid = true;

	if (unlikely(!v))
		return true;

	if (vhost_get_used_event(vq, &event)) {
		vq_err(vq, "Failed to get used event idx");
		return true;
	}
	return vring_need_event(vhost16_to_cpu(vq, event), new, old);
}