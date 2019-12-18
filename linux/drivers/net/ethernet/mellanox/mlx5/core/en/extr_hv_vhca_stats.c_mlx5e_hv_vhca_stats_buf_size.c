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
struct mlx5e_priv {int max_nch; } ;
struct mlx5e_hv_vhca_per_ring_stats {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int mlx5e_hv_vhca_stats_buf_size(struct mlx5e_priv *priv)
{
	return (sizeof(struct mlx5e_hv_vhca_per_ring_stats) *
		priv->max_nch);
}