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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp ; 
 int /*<<< orphan*/  swp_csum ; 
 int /*<<< orphan*/  swp_lso ; 

__attribute__((used)) static inline bool mlx5_tx_swp_supported(struct mlx5_core_dev *mdev)
{
	return MLX5_CAP_ETH(mdev, swp) &&
		MLX5_CAP_ETH(mdev, swp_csum) && MLX5_CAP_ETH(mdev, swp_lso);
}