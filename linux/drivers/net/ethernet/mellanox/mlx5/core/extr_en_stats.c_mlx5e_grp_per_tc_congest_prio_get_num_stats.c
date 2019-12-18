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
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS ; 
 int NUM_PPORT_PRIO ; 
 int /*<<< orphan*/  sbcam_reg ; 

__attribute__((used)) static int mlx5e_grp_per_tc_congest_prio_get_num_stats(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;

	if (!MLX5_CAP_GEN(mdev, sbcam_reg))
		return 0;

	return NUM_PPORT_PER_TC_CONGEST_PRIO_COUNTERS * NUM_PPORT_PRIO;
}