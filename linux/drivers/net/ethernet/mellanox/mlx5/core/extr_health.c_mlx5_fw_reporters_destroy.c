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
struct mlx5_core_health {int /*<<< orphan*/  fw_fatal_reporter; int /*<<< orphan*/  fw_reporter; } ;
struct TYPE_2__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_health_reporter_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_fw_reporters_destroy(struct mlx5_core_dev *dev)
{
	struct mlx5_core_health *health = &dev->priv.health;

	if (!IS_ERR_OR_NULL(health->fw_reporter))
		devlink_health_reporter_destroy(health->fw_reporter);

	if (!IS_ERR_OR_NULL(health->fw_fatal_reporter))
		devlink_health_reporter_destroy(health->fw_fatal_reporter);
}