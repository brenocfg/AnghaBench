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
struct veth_rq {int rx_notify_masked; int /*<<< orphan*/  xdp_ring; int /*<<< orphan*/  xdp_napi; } ;
struct veth_priv {struct veth_rq* rq; } ;
struct net_device {int real_num_rx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_hash_del (int /*<<< orphan*/ *) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_ring_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  veth_ptr_free ; 

__attribute__((used)) static void veth_napi_del(struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	int i;

	for (i = 0; i < dev->real_num_rx_queues; i++) {
		struct veth_rq *rq = &priv->rq[i];

		napi_disable(&rq->xdp_napi);
		napi_hash_del(&rq->xdp_napi);
	}
	synchronize_net();

	for (i = 0; i < dev->real_num_rx_queues; i++) {
		struct veth_rq *rq = &priv->rq[i];

		netif_napi_del(&rq->xdp_napi);
		rq->rx_notify_masked = false;
		ptr_ring_cleanup(&rq->xdp_ring, veth_ptr_free);
	}
}