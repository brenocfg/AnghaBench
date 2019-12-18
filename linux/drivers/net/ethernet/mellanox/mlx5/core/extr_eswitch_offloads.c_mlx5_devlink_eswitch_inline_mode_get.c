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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  inline_mode; } ;
struct mlx5_eswitch {TYPE_2__ offloads; } ;
struct TYPE_3__ {struct mlx5_eswitch* eswitch; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int esw_inline_mode_to_devlink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5_devlink_eswitch_check (struct devlink*) ; 

int mlx5_devlink_eswitch_inline_mode_get(struct devlink *devlink, u8 *mode)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	struct mlx5_eswitch *esw = dev->priv.eswitch;
	int err;

	err = mlx5_devlink_eswitch_check(devlink);
	if (err)
		return err;

	return esw_inline_mode_to_devlink(esw->offloads.inline_mode, mode);
}