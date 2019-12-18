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
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_of_uars_per_page ; 
 int /*<<< orphan*/  uar_4k ; 

__attribute__((used)) static int uars_per_sys_page(struct mlx5_core_dev *mdev)
{
	if (MLX5_CAP_GEN(mdev, uar_4k))
		return MLX5_CAP_GEN(mdev, num_of_uars_per_page);

	return 1;
}