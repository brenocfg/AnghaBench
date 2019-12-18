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
struct vhost_virtqueue {int /*<<< orphan*/  last_avail_idx; int /*<<< orphan*/  avail_idx; } ;
struct vhost_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio16 ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost16_to_cpu (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 int vhost_get_avail_idx (struct vhost_virtqueue*,int /*<<< orphan*/ *) ; 

bool vhost_vq_avail_empty(struct vhost_dev *dev, struct vhost_virtqueue *vq)
{
	__virtio16 avail_idx;
	int r;

	if (vq->avail_idx != vq->last_avail_idx)
		return false;

	r = vhost_get_avail_idx(vq, &avail_idx);
	if (unlikely(r))
		return false;
	vq->avail_idx = vhost16_to_cpu(vq, avail_idx);

	return vq->avail_idx == vq->last_avail_idx;
}