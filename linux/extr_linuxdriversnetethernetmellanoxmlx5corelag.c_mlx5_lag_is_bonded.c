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
struct mlx5_lag {int flags; } ;

/* Variables and functions */
 int MLX5_LAG_FLAG_BONDED ; 

__attribute__((used)) static bool mlx5_lag_is_bonded(struct mlx5_lag *ldev)
{
	return !!(ldev->flags & MLX5_LAG_FLAG_BONDED);
}