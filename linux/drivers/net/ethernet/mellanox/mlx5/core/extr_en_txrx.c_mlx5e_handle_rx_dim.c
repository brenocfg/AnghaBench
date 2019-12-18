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
struct mlx5e_rq_stats {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_ctr; } ;
struct mlx5e_rq {int /*<<< orphan*/  dim; TYPE_1__ cq; int /*<<< orphan*/  state; struct mlx5e_rq_stats* stats; } ;
struct dim_sample {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_AM ; 
 int /*<<< orphan*/  dim_update_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dim_sample*) ; 
 int /*<<< orphan*/  net_dim (int /*<<< orphan*/ *,struct dim_sample) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlx5e_handle_rx_dim(struct mlx5e_rq *rq)
{
	struct mlx5e_rq_stats *stats = rq->stats;
	struct dim_sample dim_sample = {};

	if (unlikely(!test_bit(MLX5E_RQ_STATE_AM, &rq->state)))
		return;

	dim_update_sample(rq->cq.event_ctr, stats->packets, stats->bytes, &dim_sample);
	net_dim(&rq->dim, dim_sample);
}