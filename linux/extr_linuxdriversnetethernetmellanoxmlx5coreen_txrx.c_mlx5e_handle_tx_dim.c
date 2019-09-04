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
struct net_dim_sample {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_ctr; } ;
struct mlx5e_txqsq {int /*<<< orphan*/  dim; TYPE_1__ cq; int /*<<< orphan*/  state; struct mlx5e_sq_stats* stats; } ;
struct mlx5e_sq_stats {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_SQ_STATE_AM ; 
 int /*<<< orphan*/  net_dim (int /*<<< orphan*/ *,struct net_dim_sample) ; 
 int /*<<< orphan*/  net_dim_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_dim_sample*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlx5e_handle_tx_dim(struct mlx5e_txqsq *sq)
{
	struct mlx5e_sq_stats *stats = sq->stats;
	struct net_dim_sample dim_sample;

	if (unlikely(!test_bit(MLX5E_SQ_STATE_AM, &sq->state)))
		return;

	net_dim_sample(sq->cq.event_ctr, stats->packets, stats->bytes,
		       &dim_sample);
	net_dim(&sq->dim, dim_sample);
}