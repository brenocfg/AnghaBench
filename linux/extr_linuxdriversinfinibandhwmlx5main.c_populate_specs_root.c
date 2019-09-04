#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uverbs_object_tree_def {int dummy; } ;
struct TYPE_2__ {struct uverbs_object_tree_def const** driver_specs; } ;
struct mlx5_ib_dev {TYPE_1__ ib_dev; struct uverbs_object_tree_def** driver_trees; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct uverbs_object_tree_def**) ; 
 int MLX5_ACCEL_IPSEC_CAP_DEVICE ; 
 scalar_t__ MLX5_CAP_DEV_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_GENERAL_OBJ_TYPES_CAP_UCTX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  general_obj_types ; 
 int /*<<< orphan*/  memic ; 
 int mlx5_accel_ipsec_device_caps (int /*<<< orphan*/ ) ; 
 struct uverbs_object_tree_def mlx5_ib_dm ; 
 struct uverbs_object_tree_def mlx5_ib_flow_action ; 
 struct uverbs_object_tree_def* mlx5_ib_get_devx_tree () ; 
 scalar_t__ mlx5_ib_get_flow_trees (struct uverbs_object_tree_def const**) ; 

__attribute__((used)) static int populate_specs_root(struct mlx5_ib_dev *dev)
{
	const struct uverbs_object_tree_def **trees = dev->driver_trees;
	size_t num_trees = 0;

	if (mlx5_accel_ipsec_device_caps(dev->mdev) &
	    MLX5_ACCEL_IPSEC_CAP_DEVICE)
		trees[num_trees++] = &mlx5_ib_flow_action;

	if (MLX5_CAP_DEV_MEM(dev->mdev, memic))
		trees[num_trees++] = &mlx5_ib_dm;

	if (MLX5_CAP_GEN_64(dev->mdev, general_obj_types) &
	    MLX5_GENERAL_OBJ_TYPES_CAP_UCTX)
		trees[num_trees++] = mlx5_ib_get_devx_tree();

	num_trees += mlx5_ib_get_flow_trees(trees + num_trees);

	WARN_ON(num_trees >= ARRAY_SIZE(dev->driver_trees));
	trees[num_trees] = NULL;
	dev->ib_dev.driver_specs = trees;

	return 0;
}