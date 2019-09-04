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
struct TYPE_2__ {int /*<<< orphan*/  res_id; int /*<<< orphan*/  owner; } ;
struct res_fs_rule {TYPE_1__ com; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_DETACH ; 
 int /*<<< orphan*/  RES_FS_RULE ; 
 int /*<<< orphan*/  mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int rem_res_range (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_undo_mirror_rule(struct mlx4_dev *dev, struct res_fs_rule *fs_rule)
{
	int err;

	err = rem_res_range(dev, fs_rule->com.owner, fs_rule->com.res_id, 1, RES_FS_RULE, 0);
	if (err) {
		mlx4_err(dev, "Fail to remove flow steering resources\n");
		return err;
	}

	mlx4_cmd(dev, fs_rule->com.res_id, 0, 0, MLX4_QP_FLOW_STEERING_DETACH,
		 MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	return 0;
}