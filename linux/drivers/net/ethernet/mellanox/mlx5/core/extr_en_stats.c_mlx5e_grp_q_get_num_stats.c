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
struct mlx5e_priv {scalar_t__ drop_rq_q_counter; scalar_t__ q_counter; } ;

/* Variables and functions */
 scalar_t__ NUM_DROP_RQ_COUNTERS ; 
 scalar_t__ NUM_Q_COUNTERS ; 

__attribute__((used)) static int mlx5e_grp_q_get_num_stats(struct mlx5e_priv *priv)
{
	int num_stats = 0;

	if (priv->q_counter)
		num_stats += NUM_Q_COUNTERS;

	if (priv->drop_rq_q_counter)
		num_stats += NUM_DROP_RQ_COUNTERS;

	return num_stats;
}