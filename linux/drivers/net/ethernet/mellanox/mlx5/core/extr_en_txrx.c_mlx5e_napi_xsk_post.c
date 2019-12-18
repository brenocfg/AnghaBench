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
struct mlx5e_xdpsq {int dummy; } ;
struct mlx5e_rq {int (* post_wqes ) (struct mlx5e_rq*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_TX_XSK_POLL_BUDGET ; 
 int mlx5e_xsk_tx (struct mlx5e_xdpsq*,int /*<<< orphan*/ ) ; 
 int mlx5e_xsk_update_rx_wakeup (struct mlx5e_rq*,int) ; 
 int /*<<< orphan*/  mlx5e_xsk_update_tx_wakeup (struct mlx5e_xdpsq*) ; 
 int stub1 (struct mlx5e_rq*) ; 

__attribute__((used)) static bool mlx5e_napi_xsk_post(struct mlx5e_xdpsq *xsksq, struct mlx5e_rq *xskrq)
{
	bool busy_xsk = false, xsk_rx_alloc_err;

	/* Handle the race between the application querying need_wakeup and the
	 * driver setting it:
	 * 1. Update need_wakeup both before and after the TX. If it goes to
	 * "yes", it can only happen with the first update.
	 * 2. If the application queried need_wakeup before we set it, the
	 * packets will be transmitted anyway, even w/o a wakeup.
	 * 3. Give a chance to clear need_wakeup after new packets were queued
	 * for TX.
	 */
	mlx5e_xsk_update_tx_wakeup(xsksq);
	busy_xsk |= mlx5e_xsk_tx(xsksq, MLX5E_TX_XSK_POLL_BUDGET);
	mlx5e_xsk_update_tx_wakeup(xsksq);

	xsk_rx_alloc_err = xskrq->post_wqes(xskrq);
	busy_xsk |= mlx5e_xsk_update_rx_wakeup(xskrq, xsk_rx_alloc_err);

	return busy_xsk;
}