#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dim_cq_moder {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct mlx5e_params {struct dim_cq_moder tx_cq_moderation; struct dim_cq_moder rx_cq_moderation; } ;
struct mlx5e_channel_param {int /*<<< orphan*/  xdp_sq; int /*<<< orphan*/  rq; int /*<<< orphan*/  icosq; int /*<<< orphan*/  tx_cq; int /*<<< orphan*/  rx_cq; int /*<<< orphan*/  icosq_cq; } ;
struct TYPE_9__ {int /*<<< orphan*/  cq; } ;
struct TYPE_7__ {int /*<<< orphan*/  cq; } ;
struct TYPE_8__ {int /*<<< orphan*/  cq; } ;
struct mlx5e_channel {TYPE_3__ icosq; TYPE_1__ xdpsq; TYPE_2__ rq; TYPE_1__ rq_xdpsq; scalar_t__ xdp; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_close_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_icosq (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_close_rq (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5e_close_sqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_tx_cqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_xdpsq (TYPE_1__*) ; 
 int mlx5e_open_cq (struct mlx5e_channel*,struct dim_cq_moder,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5e_open_icosq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int mlx5e_open_rq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int mlx5e_open_sqs (struct mlx5e_channel*,struct mlx5e_params*,struct mlx5e_channel_param*) ; 
 int mlx5e_open_tx_cqs (struct mlx5e_channel*,struct mlx5e_params*,struct mlx5e_channel_param*) ; 
 int mlx5e_open_xdpsq (struct mlx5e_channel*,struct mlx5e_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_open_queues(struct mlx5e_channel *c,
			     struct mlx5e_params *params,
			     struct mlx5e_channel_param *cparam)
{
	struct dim_cq_moder icocq_moder = {0, 0};
	int err;

	err = mlx5e_open_cq(c, icocq_moder, &cparam->icosq_cq, &c->icosq.cq);
	if (err)
		return err;

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
				     &cparam->tx_cq, &c->rq_xdpsq.cq) : 0;
	if (err)
		goto err_close_rx_cq;

	napi_enable(&c->napi);

	err = mlx5e_open_icosq(c, params, &cparam->icosq, &c->icosq);
	if (err)
		goto err_disable_napi;

	err = mlx5e_open_sqs(c, params, cparam);
	if (err)
		goto err_close_icosq;

	if (c->xdp) {
		err = mlx5e_open_xdpsq(c, params, &cparam->xdp_sq, NULL,
				       &c->rq_xdpsq, false);
		if (err)
			goto err_close_sqs;
	}

	err = mlx5e_open_rq(c, params, &cparam->rq, NULL, NULL, &c->rq);
	if (err)
		goto err_close_xdp_sq;

	err = mlx5e_open_xdpsq(c, params, &cparam->xdp_sq, NULL, &c->xdpsq, true);
	if (err)
		goto err_close_rq;

	return 0;

err_close_rq:
	mlx5e_close_rq(&c->rq);

err_close_xdp_sq:
	if (c->xdp)
		mlx5e_close_xdpsq(&c->rq_xdpsq);

err_close_sqs:
	mlx5e_close_sqs(c);

err_close_icosq:
	mlx5e_close_icosq(&c->icosq);

err_disable_napi:
	napi_disable(&c->napi);

	if (c->xdp)
		mlx5e_close_cq(&c->rq_xdpsq.cq);

err_close_rx_cq:
	mlx5e_close_cq(&c->rq.cq);

err_close_xdp_tx_cqs:
	mlx5e_close_cq(&c->xdpsq.cq);

err_close_tx_cqs:
	mlx5e_close_tx_cqs(c);

err_close_icosq_cq:
	mlx5e_close_cq(&c->icosq.cq);

	return err;
}