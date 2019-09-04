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
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_MAX_UMR_SHIFT ; 
 int MR_CACHE_LAST_STD_ENTRY ; 
 int /*<<< orphan*/  umr_extended_translation_offset ; 

__attribute__((used)) static int mr_cache_max_order(struct mlx5_ib_dev *dev)
{
	if (MLX5_CAP_GEN(dev->mdev, umr_extended_translation_offset))
		return MR_CACHE_LAST_STD_ENTRY + 2;
	return MLX5_MAX_UMR_SHIFT;
}