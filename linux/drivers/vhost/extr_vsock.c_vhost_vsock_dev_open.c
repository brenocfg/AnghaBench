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
struct vhost_vsock {int /*<<< orphan*/  send_pkt_work; int /*<<< orphan*/  send_pkt_list; int /*<<< orphan*/  send_pkt_list_lock; struct vhost_virtqueue* vqs; int /*<<< orphan*/  dev; int /*<<< orphan*/  queued_replies; scalar_t__ guest_cid; } ;
struct vhost_virtqueue {int /*<<< orphan*/  handle_kick; } ;
struct inode {int dummy; } ;
struct file {struct vhost_vsock* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct vhost_virtqueue*) ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UIO_MAXIOV ; 
 int /*<<< orphan*/  VHOST_VSOCK_PKT_WEIGHT ; 
 int /*<<< orphan*/  VHOST_VSOCK_WEIGHT ; 
 size_t VSOCK_VQ_RX ; 
 size_t VSOCK_VQ_TX ; 
 int __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vhost_virtqueue** kmalloc_array (int /*<<< orphan*/ ,int,int) ; 
 struct vhost_vsock* kvmalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_dev_init (int /*<<< orphan*/ *,struct vhost_virtqueue**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_transport_send_pkt_work ; 
 int /*<<< orphan*/  vhost_vsock_free (struct vhost_vsock*) ; 
 int /*<<< orphan*/  vhost_vsock_handle_rx_kick ; 
 int /*<<< orphan*/  vhost_vsock_handle_tx_kick ; 
 int /*<<< orphan*/  vhost_work_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhost_vsock_dev_open(struct inode *inode, struct file *file)
{
	struct vhost_virtqueue **vqs;
	struct vhost_vsock *vsock;
	int ret;

	/* This struct is large and allocation could fail, fall back to vmalloc
	 * if there is no other way.
	 */
	vsock = kvmalloc(sizeof(*vsock), GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!vsock)
		return -ENOMEM;

	vqs = kmalloc_array(ARRAY_SIZE(vsock->vqs), sizeof(*vqs), GFP_KERNEL);
	if (!vqs) {
		ret = -ENOMEM;
		goto out;
	}

	vsock->guest_cid = 0; /* no CID assigned yet */

	atomic_set(&vsock->queued_replies, 0);

	vqs[VSOCK_VQ_TX] = &vsock->vqs[VSOCK_VQ_TX];
	vqs[VSOCK_VQ_RX] = &vsock->vqs[VSOCK_VQ_RX];
	vsock->vqs[VSOCK_VQ_TX].handle_kick = vhost_vsock_handle_tx_kick;
	vsock->vqs[VSOCK_VQ_RX].handle_kick = vhost_vsock_handle_rx_kick;

	vhost_dev_init(&vsock->dev, vqs, ARRAY_SIZE(vsock->vqs),
		       UIO_MAXIOV, VHOST_VSOCK_PKT_WEIGHT,
		       VHOST_VSOCK_WEIGHT);

	file->private_data = vsock;
	spin_lock_init(&vsock->send_pkt_list_lock);
	INIT_LIST_HEAD(&vsock->send_pkt_list);
	vhost_work_init(&vsock->send_pkt_work, vhost_transport_send_pkt_work);
	return 0;

out:
	vhost_vsock_free(vsock);
	return ret;
}