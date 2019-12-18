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
struct vhost_virtqueue {int /*<<< orphan*/  poll; TYPE_1__* heads; } ;
struct vhost_net_ubuf_ref {struct vhost_virtqueue* vq; } ;
struct ubuf_info {size_t desc; struct vhost_net_ubuf_ref* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_DMA_DONE_LEN ; 
 int /*<<< orphan*/  VHOST_DMA_FAILED_LEN ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int vhost_net_ubuf_put (struct vhost_net_ubuf_ref*) ; 
 int /*<<< orphan*/  vhost_poll_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_zerocopy_callback(struct ubuf_info *ubuf, bool success)
{
	struct vhost_net_ubuf_ref *ubufs = ubuf->ctx;
	struct vhost_virtqueue *vq = ubufs->vq;
	int cnt;

	rcu_read_lock_bh();

	/* set len to mark this desc buffers done DMA */
	vq->heads[ubuf->desc].len = success ?
		VHOST_DMA_DONE_LEN : VHOST_DMA_FAILED_LEN;
	cnt = vhost_net_ubuf_put(ubufs);

	/*
	 * Trigger polling thread if guest stopped submitting new buffers:
	 * in this case, the refcount after decrement will eventually reach 1.
	 * We also trigger polling periodically after each 16 packets
	 * (the value 16 here is more or less arbitrary, it's tuned to trigger
	 * less than 10% of times).
	 */
	if (cnt <= 1 || !(cnt % 16))
		vhost_poll_queue(&vq->poll);

	rcu_read_unlock_bh();
}