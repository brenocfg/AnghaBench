#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mem; } ;
struct veth_rq {TYPE_1__ xdp_rxq; int /*<<< orphan*/  xdp_prog; int /*<<< orphan*/  xdp_mem; } ;
struct veth_priv {struct veth_rq* rq; int /*<<< orphan*/  _xdp_prog; } ;
struct net_device {int real_num_rx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_TYPE_PAGE_SHARED ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int veth_napi_add (struct net_device*) ; 
 int /*<<< orphan*/  xdp_rxq_info_is_reg (TYPE_1__*) ; 
 int xdp_rxq_info_reg (TYPE_1__*,struct net_device*,int) ; 
 int xdp_rxq_info_reg_mem_model (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (TYPE_1__*) ; 

__attribute__((used)) static int veth_enable_xdp(struct net_device *dev)
{
	struct veth_priv *priv = netdev_priv(dev);
	int err, i;

	if (!xdp_rxq_info_is_reg(&priv->rq[0].xdp_rxq)) {
		for (i = 0; i < dev->real_num_rx_queues; i++) {
			struct veth_rq *rq = &priv->rq[i];

			err = xdp_rxq_info_reg(&rq->xdp_rxq, dev, i);
			if (err < 0)
				goto err_rxq_reg;

			err = xdp_rxq_info_reg_mem_model(&rq->xdp_rxq,
							 MEM_TYPE_PAGE_SHARED,
							 NULL);
			if (err < 0)
				goto err_reg_mem;

			/* Save original mem info as it can be overwritten */
			rq->xdp_mem = rq->xdp_rxq.mem;
		}

		err = veth_napi_add(dev);
		if (err)
			goto err_rxq_reg;
	}

	for (i = 0; i < dev->real_num_rx_queues; i++)
		rcu_assign_pointer(priv->rq[i].xdp_prog, priv->_xdp_prog);

	return 0;
err_reg_mem:
	xdp_rxq_info_unreg(&priv->rq[i].xdp_rxq);
err_rxq_reg:
	for (i--; i >= 0; i--)
		xdp_rxq_info_unreg(&priv->rq[i].xdp_rxq);

	return err;
}