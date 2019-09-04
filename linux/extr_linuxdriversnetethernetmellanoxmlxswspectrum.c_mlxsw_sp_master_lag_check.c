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
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct netdev_lag_upper_info {scalar_t__ tx_type; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ NETDEV_LAG_TX_TYPE_HASH ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ mlxsw_sp_lag_index_get (struct mlxsw_sp*,struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
mlxsw_sp_master_lag_check(struct mlxsw_sp *mlxsw_sp,
			  struct net_device *lag_dev,
			  struct netdev_lag_upper_info *lag_upper_info,
			  struct netlink_ext_ack *extack)
{
	u16 lag_id;

	if (mlxsw_sp_lag_index_get(mlxsw_sp, lag_dev, &lag_id) != 0) {
		NL_SET_ERR_MSG_MOD(extack, "Exceeded number of supported LAG devices");
		return false;
	}
	if (lag_upper_info->tx_type != NETDEV_LAG_TX_TYPE_HASH) {
		NL_SET_ERR_MSG_MOD(extack, "LAG device using unsupported Tx type");
		return false;
	}
	return true;
}