#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct net_dim_cq_moder {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {TYPE_4__* channel_stats; TYPE_11__* mdev; struct net_device* netdev; int /*<<< orphan*/  tstamp; } ;
struct mlx5e_params {struct net_dim_cq_moder tx_cq_moderation; struct net_dim_cq_moder rx_cq_moderation; int /*<<< orphan*/  xdp_prog; int /*<<< orphan*/  num_tc; } ;
struct mlx5e_channel_param {int /*<<< orphan*/  xdp_sq; int /*<<< orphan*/  rq; int /*<<< orphan*/  icosq; int /*<<< orphan*/  tx_cq; int /*<<< orphan*/  rx_cq; int /*<<< orphan*/  icosq_cq; } ;
struct TYPE_19__ {int /*<<< orphan*/  cq; } ;
struct TYPE_17__ {int /*<<< orphan*/  cq; } ;
struct TYPE_18__ {int /*<<< orphan*/  cq; TYPE_5__ xdpsq; } ;
struct mlx5e_channel {int ix; int cpu; int xdp; int /*<<< orphan*/  napi; TYPE_7__ icosq; TYPE_5__ xdpsq; TYPE_6__ rq; int /*<<< orphan*/  irq_desc; int /*<<< orphan*/ * stats; int /*<<< orphan*/  num_tc; int /*<<< orphan*/  mkey_be; struct net_device* netdev; int /*<<< orphan*/ * pdev; int /*<<< orphan*/ * tstamp; TYPE_11__* mdev; struct mlx5e_priv* priv; } ;
struct TYPE_16__ {int /*<<< orphan*/  ch; } ;
struct TYPE_14__ {int /*<<< orphan*/  key; } ;
struct TYPE_15__ {TYPE_2__ mkey; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {TYPE_3__ mlx5e_res; TYPE_1__* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  kvfree (struct mlx5e_channel*) ; 
 struct mlx5e_channel* kvzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_vector2eqn (TYPE_11__*,int,int*,unsigned int*) ; 
 int /*<<< orphan*/  mlx5e_close_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_icosq (TYPE_7__*) ; 
 int /*<<< orphan*/  mlx5e_close_rq (TYPE_6__*) ; 
 int /*<<< orphan*/  mlx5e_close_sqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_tx_cqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_xdpsq (TYPE_5__*) ; 
 int mlx5e_get_cpu (struct mlx5e_priv*,int) ; 
 int /*<<< orphan*/  mlx5e_napi_poll ; 
 int mlx5e_open_cq (struct mlx5e_channel*,struct net_dim_cq_moder,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5e_open_icosq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int mlx5e_open_rq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int mlx5e_open_sqs (struct mlx5e_channel*,struct mlx5e_params*,struct mlx5e_channel_param*) ; 
 int mlx5e_open_tx_cqs (struct mlx5e_channel*,struct mlx5e_params*,struct mlx5e_channel_param*) ; 
 int mlx5e_open_xdpsq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_open_channel(struct mlx5e_priv *priv, int ix,
			      struct mlx5e_params *params,
			      struct mlx5e_channel_param *cparam,
			      struct mlx5e_channel **cp)
{
	struct net_dim_cq_moder icocq_moder = {0, 0};
	struct net_device *netdev = priv->netdev;
	int cpu = mlx5e_get_cpu(priv, ix);
	struct mlx5e_channel *c;
	unsigned int irq;
	int err;
	int eqn;

	err = mlx5_vector2eqn(priv->mdev, ix, &eqn, &irq);
	if (err)
		return err;

	c = kvzalloc_node(sizeof(*c), GFP_KERNEL, cpu_to_node(cpu));
	if (!c)
		return -ENOMEM;

	c->priv     = priv;
	c->mdev     = priv->mdev;
	c->tstamp   = &priv->tstamp;
	c->ix       = ix;
	c->cpu      = cpu;
	c->pdev     = &priv->mdev->pdev->dev;
	c->netdev   = priv->netdev;
	c->mkey_be  = cpu_to_be32(priv->mdev->mlx5e_res.mkey.key);
	c->num_tc   = params->num_tc;
	c->xdp      = !!params->xdp_prog;
	c->stats    = &priv->channel_stats[ix].ch;

	c->irq_desc = irq_to_desc(irq);

	netif_napi_add(netdev, &c->napi, mlx5e_napi_poll, 64);

	err = mlx5e_open_cq(c, icocq_moder, &cparam->icosq_cq, &c->icosq.cq);
	if (err)
		goto err_napi_del;

	err = mlx5e_open_tx_cqs(c, params, cparam);
	if (err)
		goto err_close_icosq_cq;

	err = mlx5e_open_cq(c, params->tx_cq_moderation, &cparam->tx_cq, &c->xdpsq.cq);
	if (err)
		goto err_close_tx_cqs;

	err = mlx5e_open_cq(c, params->rx_cq_moderation, &cparam->rx_cq, &c->rq.cq);
	if (err)
		goto err_close_xdp_tx_cqs;

	/* XDP SQ CQ params are same as normal TXQ sq CQ params */
	err = c->xdp ? mlx5e_open_cq(c, params->tx_cq_moderation,
				     &cparam->tx_cq, &c->rq.xdpsq.cq) : 0;
	if (err)
		goto err_close_rx_cq;

	napi_enable(&c->napi);

	err = mlx5e_open_icosq(c, params, &cparam->icosq, &c->icosq);
	if (err)
		goto err_disable_napi;

	err = mlx5e_open_sqs(c, params, cparam);
	if (err)
		goto err_close_icosq;

	err = c->xdp ? mlx5e_open_xdpsq(c, params, &cparam->xdp_sq, &c->rq.xdpsq, false) : 0;
	if (err)
		goto err_close_sqs;

	err = mlx5e_open_rq(c, params, &cparam->rq, &c->rq);
	if (err)
		goto err_close_xdp_sq;

	err = mlx5e_open_xdpsq(c, params, &cparam->xdp_sq, &c->xdpsq, true);
	if (err)
		goto err_close_rq;

	*cp = c;

	return 0;

err_close_rq:
	mlx5e_close_rq(&c->rq);

err_close_xdp_sq:
	if (c->xdp)
		mlx5e_close_xdpsq(&c->rq.xdpsq);

err_close_sqs:
	mlx5e_close_sqs(c);

err_close_icosq:
	mlx5e_close_icosq(&c->icosq);

err_disable_napi:
	napi_disable(&c->napi);
	if (c->xdp)
		mlx5e_close_cq(&c->rq.xdpsq.cq);

err_close_rx_cq:
	mlx5e_close_cq(&c->rq.cq);

err_close_xdp_tx_cqs:
	mlx5e_close_cq(&c->xdpsq.cq);

err_close_tx_cqs:
	mlx5e_close_tx_cqs(c);

err_close_icosq_cq:
	mlx5e_close_cq(&c->icosq.cq);

err_napi_del:
	netif_napi_del(&c->napi);
	kvfree(c);

	return err;
}