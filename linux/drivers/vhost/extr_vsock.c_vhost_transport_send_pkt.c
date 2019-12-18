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
struct TYPE_2__ {int /*<<< orphan*/  dst_cid; } ;
struct virtio_vsock_pkt {int len; int /*<<< orphan*/  list; scalar_t__ reply; TYPE_1__ hdr; } ;
struct vhost_vsock {int /*<<< orphan*/  send_pkt_work; int /*<<< orphan*/  dev; int /*<<< orphan*/  send_pkt_list_lock; int /*<<< orphan*/  send_pkt_list; int /*<<< orphan*/  queued_replies; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct vhost_vsock* vhost_vsock_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_work_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtio_transport_free_pkt (struct virtio_vsock_pkt*) ; 

__attribute__((used)) static int
vhost_transport_send_pkt(struct virtio_vsock_pkt *pkt)
{
	struct vhost_vsock *vsock;
	int len = pkt->len;

	rcu_read_lock();

	/* Find the vhost_vsock according to guest context id  */
	vsock = vhost_vsock_get(le64_to_cpu(pkt->hdr.dst_cid));
	if (!vsock) {
		rcu_read_unlock();
		virtio_transport_free_pkt(pkt);
		return -ENODEV;
	}

	if (pkt->reply)
		atomic_inc(&vsock->queued_replies);

	spin_lock_bh(&vsock->send_pkt_list_lock);
	list_add_tail(&pkt->list, &vsock->send_pkt_list);
	spin_unlock_bh(&vsock->send_pkt_list_lock);

	vhost_work_queue(&vsock->dev, &vsock->send_pkt_work);

	rcu_read_unlock();
	return len;
}