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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct in_validator_info {int /*<<< orphan*/  extack; TYPE_1__* ivi_dev; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int __mlxsw_sp_inetaddr_event (struct mlxsw_sp*,struct net_device*,unsigned long,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 struct mlxsw_sp_rif* mlxsw_sp_rif_find_by_dev (struct mlxsw_sp*,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_rif_should_config (struct mlxsw_sp_rif*,struct net_device*,unsigned long) ; 
 int mlxsw_sp_router_port_check_rif_addr (struct mlxsw_sp*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int notifier_from_errno (int) ; 

int mlxsw_sp_inetaddr_valid_event(struct notifier_block *unused,
				  unsigned long event, void *ptr)
{
	struct in_validator_info *ivi = (struct in_validator_info *) ptr;
	struct net_device *dev = ivi->ivi_dev->dev;
	struct mlxsw_sp *mlxsw_sp;
	struct mlxsw_sp_rif *rif;
	int err = 0;

	mlxsw_sp = mlxsw_sp_lower_get(dev);
	if (!mlxsw_sp)
		goto out;

	rif = mlxsw_sp_rif_find_by_dev(mlxsw_sp, dev);
	if (!mlxsw_sp_rif_should_config(rif, dev, event))
		goto out;

	err = mlxsw_sp_router_port_check_rif_addr(mlxsw_sp, dev, dev->dev_addr,
						  ivi->extack);
	if (err)
		goto out;

	err = __mlxsw_sp_inetaddr_event(mlxsw_sp, dev, event, ivi->extack);
out:
	return notifier_from_errno(err);
}