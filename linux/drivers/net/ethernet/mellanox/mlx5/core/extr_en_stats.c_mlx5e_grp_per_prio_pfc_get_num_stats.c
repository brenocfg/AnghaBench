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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int NUM_PPORT_PER_PRIO_PFC_COUNTERS ; 
 int NUM_PPORT_PFC_STALL_COUNTERS (struct mlx5e_priv*) ; 
 int hweight8 (int /*<<< orphan*/ ) ; 
 int mlx5e_query_global_pause_combined (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_query_pfc_combined (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_grp_per_prio_pfc_get_num_stats(struct mlx5e_priv *priv)
{
	return (mlx5e_query_global_pause_combined(priv) +
		hweight8(mlx5e_query_pfc_combined(priv))) *
		NUM_PPORT_PER_PRIO_PFC_COUNTERS +
		NUM_PPORT_PFC_STALL_COUNTERS(priv);
}