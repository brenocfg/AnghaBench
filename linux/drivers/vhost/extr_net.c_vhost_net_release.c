#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ page; } ;
struct TYPE_9__ {int /*<<< orphan*/  vqs; } ;
struct vhost_net {int /*<<< orphan*/  refcnt_bias; TYPE_3__ page_frag; TYPE_4__ dev; TYPE_2__* vqs; } ;
struct socket {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct vhost_net* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  xdp; TYPE_1__ rxq; } ;

/* Variables and functions */
 size_t VHOST_NET_VQ_RX ; 
 size_t VHOST_NET_VQ_TX ; 
 int /*<<< orphan*/  __page_frag_cache_drain (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct vhost_net*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  vhost_dev_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  vhost_dev_stop (TYPE_4__*) ; 
 int /*<<< orphan*/  vhost_net_flush (struct vhost_net*) ; 
 int /*<<< orphan*/  vhost_net_stop (struct vhost_net*,struct socket**,struct socket**) ; 
 int /*<<< orphan*/  vhost_net_vq_reset (struct vhost_net*) ; 

__attribute__((used)) static int vhost_net_release(struct inode *inode, struct file *f)
{
	struct vhost_net *n = f->private_data;
	struct socket *tx_sock;
	struct socket *rx_sock;

	vhost_net_stop(n, &tx_sock, &rx_sock);
	vhost_net_flush(n);
	vhost_dev_stop(&n->dev);
	vhost_dev_cleanup(&n->dev);
	vhost_net_vq_reset(n);
	if (tx_sock)
		sockfd_put(tx_sock);
	if (rx_sock)
		sockfd_put(rx_sock);
	/* Make sure no callbacks are outstanding */
	synchronize_rcu();
	/* We do an extra flush before freeing memory,
	 * since jobs can re-queue themselves. */
	vhost_net_flush(n);
	kfree(n->vqs[VHOST_NET_VQ_RX].rxq.queue);
	kfree(n->vqs[VHOST_NET_VQ_TX].xdp);
	kfree(n->dev.vqs);
	if (n->page_frag.page)
		__page_frag_cache_drain(n->page_frag.page, n->refcnt_bias);
	kvfree(n);
	return 0;
}