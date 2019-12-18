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
 int /*<<< orphan*/  atomic ; 
 int /*<<< orphan*/  umr_modify_atomic_disabled ; 
 int /*<<< orphan*/  umr_modify_entity_size_disabled ; 

__attribute__((used)) static inline bool mlx5_ib_can_use_umr(struct mlx5_ib_dev *dev,
				       bool do_modify_atomic)
{
	if (MLX5_CAP_GEN(dev->mdev, umr_modify_entity_size_disabled))
		return false;

	if (do_modify_atomic &&
	    MLX5_CAP_GEN(dev->mdev, atomic) &&
	    MLX5_CAP_GEN(dev->mdev, umr_modify_atomic_disabled))
		return false;

	return true;
}