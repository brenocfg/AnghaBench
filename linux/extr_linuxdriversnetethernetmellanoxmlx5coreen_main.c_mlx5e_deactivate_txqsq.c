#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_4__ {TYPE_1__* wqe_info; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  uar_map; int /*<<< orphan*/  pc; int /*<<< orphan*/  sqn; TYPE_2__ db; int /*<<< orphan*/  cc; int /*<<< orphan*/  txq; int /*<<< orphan*/  state; struct mlx5_wq_cyc wq; struct mlx5e_channel* channel; } ;
struct mlx5e_tx_wqe {int /*<<< orphan*/  ctrl; } ;
struct mlx5e_channel {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_notify_hw (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5e_tx_wqe* mlx5e_post_nop (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5e_wqc_has_room_for (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_disable_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_deactivate_txqsq(struct mlx5e_txqsq *sq)
{
	struct mlx5e_channel *c = sq->channel;
	struct mlx5_wq_cyc *wq = &sq->wq;

	clear_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	/* prevent netif_tx_wake_queue */
	napi_synchronize(&c->napi);

	netif_tx_disable_queue(sq->txq);

	/* last doorbell out, godspeed .. */
	if (mlx5e_wqc_has_room_for(wq, sq->cc, sq->pc, 1)) {
		u16 pi = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
		struct mlx5e_tx_wqe *nop;

		sq->db.wqe_info[pi].skb = NULL;
		nop = mlx5e_post_nop(wq, sq->sqn, &sq->pc);
		mlx5e_notify_hw(wq, sq->pc, sq->uar_map, &nop->ctrl);
	}
}