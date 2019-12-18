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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  qcnt; } ;
struct mlx5e_priv {TYPE_1__ stats; scalar_t__ drop_rq_q_counter; scalar_t__ q_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR32_CPU (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int NUM_DROP_RQ_COUNTERS ; 
 int NUM_Q_COUNTERS ; 
 int /*<<< orphan*/  drop_rq_stats_desc ; 
 int /*<<< orphan*/  q_stats_desc ; 

__attribute__((used)) static int mlx5e_grp_q_fill_stats(struct mlx5e_priv *priv, u64 *data, int idx)
{
	int i;

	for (i = 0; i < NUM_Q_COUNTERS && priv->q_counter; i++)
		data[idx++] = MLX5E_READ_CTR32_CPU(&priv->stats.qcnt,
						   q_stats_desc, i);
	for (i = 0; i < NUM_DROP_RQ_COUNTERS && priv->drop_rq_q_counter; i++)
		data[idx++] = MLX5E_READ_CTR32_CPU(&priv->stats.qcnt,
						   drop_rq_stats_desc, i);
	return idx;
}