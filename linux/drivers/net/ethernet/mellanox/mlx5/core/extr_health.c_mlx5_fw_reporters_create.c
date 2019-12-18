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
struct mlx5_core_health {void* fw_fatal_reporter; void* fw_reporter; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MLX5_REPORTER_FW_GRACEFUL_PERIOD ; 
 int /*<<< orphan*/  PTR_ERR (void*) ; 
 void* devlink_health_reporter_create (struct devlink*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fw_fatal_reporter_ops ; 
 int /*<<< orphan*/  mlx5_fw_reporter_ops ; 
 struct devlink* priv_to_devlink (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_fw_reporters_create(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health = &dev->priv.health;
	struct devlink *devlink = priv_to_devlink(dev);

	health->fw_reporter =
		devlink_health_reporter_create(devlink, &mlx5_fw_reporter_ops,
					       0, false, dev);
	if (IS_ERR(health->fw_reporter))
		mlx5_core_warn(dev, "Failed to create fw reporter, err = %ld\n",
			       PTR_ERR(health->fw_reporter));

	health->fw_fatal_reporter =
		devlink_health_reporter_create(devlink,
					       &mlx5_fw_fatal_reporter_ops,
					       MLX5_REPORTER_FW_GRACEFUL_PERIOD,
					       true, dev);
	if (IS_ERR(health->fw_fatal_reporter))
		mlx5_core_warn(dev, "Failed to create fw fatal reporter, err = %ld\n",
			       PTR_ERR(health->fw_fatal_reporter));
}