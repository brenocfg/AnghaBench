#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {int /*<<< orphan*/  phy_statistical_counters; int /*<<< orphan*/  phy_counters; } ;
struct TYPE_7__ {TYPE_2__ pport; } ;
struct mlx5e_priv {TYPE_3__ stats; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  link_down_events; } ;
struct TYPE_8__ {TYPE_1__ phys_layer_cntrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_BE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PHY_STATISTICAL_COUNTERS ; 
 int NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS ; 
 TYPE_4__ counter_set ; 
 int /*<<< orphan*/  per_lane_error_counters ; 
 int /*<<< orphan*/  ppcnt_reg ; 
 int /*<<< orphan*/  ppcnt_statistical_group ; 
 int /*<<< orphan*/  pport_phy_statistical_err_lanes_stats_desc ; 
 int /*<<< orphan*/  pport_phy_statistical_stats_desc ; 

__attribute__((used)) static int mlx5e_grp_phy_fill_stats(struct mlx5e_priv *priv, u64 *data, int idx)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int i;

	/* link_down_events_phy has special handling since it is not stored in __be64 format */
	data[idx++] = MLX5_GET(ppcnt_reg, priv->stats.pport.phy_counters,
			       counter_set.phys_layer_cntrs.link_down_events);

	if (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		return idx;

	for (i = 0; i < NUM_PPORT_PHY_STATISTICAL_COUNTERS; i++)
		data[idx++] =
			MLX5E_READ_CTR64_BE(&priv->stats.pport.phy_statistical_counters,
					    pport_phy_statistical_stats_desc, i);

	if (MLX5_CAP_PCAM_FEATURE(mdev, per_lane_error_counters))
		for (i = 0; i < NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS; i++)
			data[idx++] =
				MLX5E_READ_CTR64_BE(&priv->stats.pport.phy_statistical_counters,
						    pport_phy_statistical_err_lanes_stats_desc,
						    i);
	return idx;
}