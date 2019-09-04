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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  eth_ext_counters; } ;
struct TYPE_4__ {TYPE_1__ pport; } ;
struct mlx5e_priv {TYPE_2__ stats; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_BE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MLX5_CAP_PCAM_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_ETH_EXT_COUNTERS ; 
 int /*<<< orphan*/  pport_eth_ext_stats_desc ; 
 int /*<<< orphan*/  rx_buffer_fullness_counters ; 

__attribute__((used)) static int mlx5e_grp_eth_ext_fill_stats(struct mlx5e_priv *priv, u64 *data,
					int idx)
{
	int i;

	if (MLX5_CAP_PCAM_FEATURE((priv)->mdev, rx_buffer_fullness_counters))
		for (i = 0; i < NUM_PPORT_ETH_EXT_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.eth_ext_counters,
						    pport_eth_ext_stats_desc, i);
	return idx;
}