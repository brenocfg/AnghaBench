#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cq; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq; } ;
struct TYPE_5__ {int /*<<< orphan*/  cq; TYPE_1__ xdpsq; } ;
struct mlx5e_channel {int /*<<< orphan*/  napi; TYPE_3__ icosq; TYPE_1__ xdpsq; TYPE_2__ rq; scalar_t__ xdp; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_icosq (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_close_rq (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5e_close_sqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_tx_cqs (struct mlx5e_channel*) ; 
 int /*<<< orphan*/  mlx5e_close_xdpsq (TYPE_1__*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_close_channel(struct mlx5e_channel *c)
{
	mlx5e_close_xdpsq(&c->xdpsq);
	mlx5e_close_rq(&c->rq);
	if (c->xdp)
		mlx5e_close_xdpsq(&c->rq.xdpsq);
	mlx5e_close_sqs(c);
	mlx5e_close_icosq(&c->icosq);
	napi_disable(&c->napi);
	if (c->xdp)
		mlx5e_close_cq(&c->rq.xdpsq.cq);
	mlx5e_close_cq(&c->rq.cq);
	mlx5e_close_cq(&c->xdpsq.cq);
	mlx5e_close_tx_cqs(c);
	mlx5e_close_cq(&c->icosq.cq);
	netif_napi_del(&c->napi);

	kvfree(c);
}