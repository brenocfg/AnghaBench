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
struct net_device {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;
struct firmware {int dummy; } ;
struct ethtool_flash {scalar_t__ region; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ ETHTOOL_FLASH_ALL_REGIONS ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int mlxsw_sp_firmware_flash (struct mlxsw_sp*,struct firmware const*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware_direct (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int mlxsw_sp_flash_device(struct net_device *dev,
				 struct ethtool_flash *flash)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	const struct firmware *firmware;
	int err;

	if (flash->region != ETHTOOL_FLASH_ALL_REGIONS)
		return -EOPNOTSUPP;

	dev_hold(dev);
	rtnl_unlock();

	err = request_firmware_direct(&firmware, flash->data, &dev->dev);
	if (err)
		goto out;
	err = mlxsw_sp_firmware_flash(mlxsw_sp, firmware);
	release_firmware(firmware);
out:
	rtnl_lock();
	dev_put(dev);
	return err;
}