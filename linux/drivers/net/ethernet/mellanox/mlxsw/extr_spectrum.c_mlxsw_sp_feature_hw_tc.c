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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  eg_acl_block; int /*<<< orphan*/  ing_acl_block; int /*<<< orphan*/  mall_tc_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_disable_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_block_disable_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ mlxsw_sp_acl_block_rule_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_feature_hw_tc(struct net_device *dev, bool enable)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);

	if (!enable) {
		if (mlxsw_sp_acl_block_rule_count(mlxsw_sp_port->ing_acl_block) ||
		    mlxsw_sp_acl_block_rule_count(mlxsw_sp_port->eg_acl_block) ||
		    !list_empty(&mlxsw_sp_port->mall_tc_list)) {
			netdev_err(dev, "Active offloaded tc filters, can't turn hw_tc_offload off\n");
			return -EINVAL;
		}
		mlxsw_sp_acl_block_disable_inc(mlxsw_sp_port->ing_acl_block);
		mlxsw_sp_acl_block_disable_inc(mlxsw_sp_port->eg_acl_block);
	} else {
		mlxsw_sp_acl_block_disable_dec(mlxsw_sp_port->ing_acl_block);
		mlxsw_sp_acl_block_disable_dec(mlxsw_sp_port->eg_acl_block);
	}
	return 0;
}