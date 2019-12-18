#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct devlink {int dummy; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 scalar_t__ MLX5_ESWITCH_NONE ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int /*<<< orphan*/  mlx5_core_is_ecpf_esw_manager (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static int mlx5_devlink_eswitch_check(struct devlink *devlink)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);

	if (MLX5_CAP_GEN(dev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		return -EOPNOTSUPP;

	if(!MLX5_ESWITCH_MANAGER(dev))
		return -EPERM;

	if (dev->priv.eswitch->mode == MLX5_ESWITCH_NONE &&
	    !mlx5_core_is_ecpf_esw_manager(dev))
		return -EOPNOTSUPP;

	return 0;
}