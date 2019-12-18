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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; struct socket* private_data; } ;
struct vhost_net_virtqueue {struct vhost_virtqueue vq; } ;
struct vhost_net {int /*<<< orphan*/  dev; struct vhost_net_virtqueue* vqs; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 size_t VHOST_NET_VQ_TX ; 
 int /*<<< orphan*/  handle_tx_copy (struct vhost_net*,struct socket*) ; 
 int /*<<< orphan*/  handle_tx_zerocopy (struct vhost_net*,struct socket*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_net_disable_vq (struct vhost_net*,struct vhost_virtqueue*) ; 
 scalar_t__ vhost_sock_zcopy (struct socket*) ; 
 int /*<<< orphan*/  vq_meta_prefetch (struct vhost_virtqueue*) ; 

__attribute__((used)) static void handle_tx(struct vhost_net *net)
{
	struct vhost_net_virtqueue *nvq = &net->vqs[VHOST_NET_VQ_TX];
	struct vhost_virtqueue *vq = &nvq->vq;
	struct socket *sock;

	mutex_lock_nested(&vq->mutex, VHOST_NET_VQ_TX);
	sock = vq->private_data;
	if (!sock)
		goto out;

	if (!vq_meta_prefetch(vq))
		goto out;

	vhost_disable_notify(&net->dev, vq);
	vhost_net_disable_vq(net, vq);

	if (vhost_sock_zcopy(sock))
		handle_tx_zerocopy(net, sock);
	else
		handle_tx_copy(net, sock);

out:
	mutex_unlock(&vq->mutex);
}