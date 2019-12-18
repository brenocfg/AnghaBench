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
struct TYPE_4__ {int /*<<< orphan*/  cq; } ;
struct TYPE_6__ {int /*<<< orphan*/  cq; } ;
struct TYPE_5__ {int /*<<< orphan*/  cq; } ;
struct mlx5e_channel {TYPE_1__ xsksq; TYPE_3__ xskicosq; TYPE_2__ xskrq; int /*<<< orphan*/  napi; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CHANNEL_STATE_XSK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_close_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_icosq (TYPE_3__*) ; 
 int /*<<< orphan*/  mlx5e_close_rq (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5e_close_xdpsq (TYPE_1__*) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 

void mlx5e_close_xsk(struct mlx5e_channel *c)
{
	clear_bit(MLX5E_CHANNEL_STATE_XSK, c->state);
	napi_synchronize(&c->napi);

	mlx5e_close_rq(&c->xskrq);
	mlx5e_close_cq(&c->xskrq.cq);
	mlx5e_close_icosq(&c->xskicosq);
	mlx5e_close_cq(&c->xskicosq.cq);
	mlx5e_close_xdpsq(&c->xsksq);
	mlx5e_close_cq(&c->xsksq.cq);
}