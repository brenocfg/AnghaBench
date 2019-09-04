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
struct mlx5e_priv {TYPE_1__* tls; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR_ATOMIC64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int NUM_TLS_SW_COUNTERS ; 
 int /*<<< orphan*/  mlx5e_tls_sw_stats_desc ; 

int mlx5e_tls_get_stats(struct mlx5e_priv *priv, u64 *data)
{
	int i, idx = 0;

	if (!priv->tls)
		return 0;

	for (i = 0; i < NUM_TLS_SW_COUNTERS; i++)
		data[idx++] =
		    MLX5E_READ_CTR_ATOMIC64(&priv->tls->sw_stats,
					    mlx5e_tls_sw_stats_desc, i);

	return NUM_TLS_SW_COUNTERS;
}