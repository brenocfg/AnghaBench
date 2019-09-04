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
struct mlx5e_priv {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_PCAM_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PHY_STATISTICAL_COUNTERS ; 
 int /*<<< orphan*/  ppcnt_statistical_group ; 

__attribute__((used)) static int mlx5e_grp_phy_get_num_stats(struct mlx5e_priv *priv)
{
	/* "1" for link_down_events special counter */
	return MLX5_CAP_PCAM_FEATURE((priv)->mdev, ppcnt_statistical_group) ?
		NUM_PPORT_PHY_STATISTICAL_COUNTERS + 1 : 1;
}