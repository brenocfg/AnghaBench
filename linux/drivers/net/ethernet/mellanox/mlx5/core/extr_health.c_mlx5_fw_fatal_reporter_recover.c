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
struct devlink_health_reporter {int dummy; } ;

/* Variables and functions */
 struct mlx5_core_dev* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int mlx5_health_try_recover (struct mlx5_core_dev*) ; 

__attribute__((used)) static int
mlx5_fw_fatal_reporter_recover(struct devlink_health_reporter *reporter,
			       void *priv_ctx)
{
	struct mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);

	return mlx5_health_try_recover(dev);
}