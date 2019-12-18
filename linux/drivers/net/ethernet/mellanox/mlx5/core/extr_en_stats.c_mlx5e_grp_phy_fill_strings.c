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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {char* format; } ;
struct TYPE_3__ {char* format; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
 scalar_t__ MLX5_CAP_PCAM_FEATURE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PHY_STATISTICAL_COUNTERS ; 
 int NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS ; 
 int /*<<< orphan*/  per_lane_error_counters ; 
 int /*<<< orphan*/  ppcnt_statistical_group ; 
 TYPE_2__* pport_phy_statistical_err_lanes_stats_desc ; 
 TYPE_1__* pport_phy_statistical_stats_desc ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mlx5e_grp_phy_fill_strings(struct mlx5e_priv *priv, u8 *data,
				      int idx)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int i;

	strcpy(data + (idx++) * ETH_GSTRING_LEN, "link_down_events_phy");

	if (!MLX5_CAP_PCAM_FEATURE(mdev, ppcnt_statistical_group))
		return idx;

	for (i = 0; i < NUM_PPORT_PHY_STATISTICAL_COUNTERS; i++)
		strcpy(data + (idx++) * ETH_GSTRING_LEN,
		       pport_phy_statistical_stats_desc[i].format);

	if (MLX5_CAP_PCAM_FEATURE(mdev, per_lane_error_counters))
		for (i = 0; i < NUM_PPORT_PHY_STATISTICAL_PER_LANE_COUNTERS; i++)
			strcpy(data + (idx++) * ETH_GSTRING_LEN,
			       pport_phy_statistical_err_lanes_stats_desc[i].format);

	return idx;
}