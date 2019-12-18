#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_txqsq {int /*<<< orphan*/  txq; int /*<<< orphan*/  state; int /*<<< orphan*/  txq_ix; TYPE_1__* channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_ENABLED ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5e_activate_txqsq(struct mlx5e_txqsq *sq)
{
	sq->txq = netdev_get_tx_queue(sq->channel->netdev, sq->txq_ix);
	set_bit(MLX5E_SQ_STATE_ENABLED, &sq->state);
	netdev_tx_reset_queue(sq->txq);
	netif_tx_start_queue(sq->txq);
}