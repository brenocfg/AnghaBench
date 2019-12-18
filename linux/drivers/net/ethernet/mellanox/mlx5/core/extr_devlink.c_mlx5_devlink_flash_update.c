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
struct netlink_ext_ack {int dummy; } ;
struct mlx5_core_dev {TYPE_1__* pdev; } ;
struct firmware {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct mlx5_core_dev* devlink_priv (struct devlink*) ; 
 int mlx5_firmware_flash (struct mlx5_core_dev*,struct firmware const*,struct netlink_ext_ack*) ; 
 int request_firmware_direct (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_devlink_flash_update(struct devlink *devlink,
				     const char *file_name,
				     const char *component,
				     struct netlink_ext_ack *extack)
{
	struct mlx5_core_dev *dev = devlink_priv(devlink);
	const struct firmware *fw;
	int err;

	if (component)
		return -EOPNOTSUPP;

	err = request_firmware_direct(&fw, file_name, &dev->pdev->dev);
	if (err)
		return err;

	return mlx5_firmware_flash(dev, fw, extack);
}