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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct devlink {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int esw_mode_to_devlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_devlink_eswitch_check (struct devlink*) ; 

int mlx5_devlink_eswitch_mode_get(struct devlink *devlink, u16 *mode)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	int err;

	err = mlx5_devlink_eswitch_check(devlink);
	if (err)
		return err;

	return esw_mode_to_devlink(dev->priv.eswitch->mode, mode);
}