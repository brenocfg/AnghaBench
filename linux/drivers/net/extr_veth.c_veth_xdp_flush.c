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
struct veth_xdp_tx_bq {int dummy; } ;
struct veth_rq {int /*<<< orphan*/  xdp_prog; } ;
struct veth_priv {struct veth_rq* rq; int /*<<< orphan*/  peer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __veth_xdp_flush (struct veth_rq*) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 size_t veth_select_rxq (struct net_device*) ; 
 int /*<<< orphan*/  veth_xdp_flush_bq (struct net_device*,struct veth_xdp_tx_bq*) ; 

__attribute__((used)) static void veth_xdp_flush(struct net_device *dev, struct veth_xdp_tx_bq *bq)
{
	struct veth_priv *rcv_priv, *priv = netdev_priv(dev);
	struct net_device *rcv;
	struct veth_rq *rq;

	rcu_read_lock();
	veth_xdp_flush_bq(dev, bq);
	rcv = rcu_dereference(priv->peer);
	if (unlikely(!rcv))
		goto out;

	rcv_priv = netdev_priv(rcv);
	rq = &rcv_priv->rq[veth_select_rxq(rcv)];
	/* xdp_ring is initialized on receive side? */
	if (unlikely(!rcu_access_pointer(rq->xdp_prog)))
		goto out;

	__veth_xdp_flush(rq);
out:
	rcu_read_unlock();
}