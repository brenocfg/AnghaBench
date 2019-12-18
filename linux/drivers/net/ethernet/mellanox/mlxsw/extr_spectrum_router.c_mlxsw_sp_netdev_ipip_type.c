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
struct net_device {scalar_t__ type; } ;
struct mlxsw_sp_router {struct mlxsw_sp_ipip_ops** ipip_ops_arr; } ;
struct mlxsw_sp_ipip_ops {scalar_t__ dev_type; } ;
struct mlxsw_sp {struct mlxsw_sp_router* router; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;

/* Variables and functions */
 int MLXSW_SP_IPIP_TYPE_MAX ; 

__attribute__((used)) static bool mlxsw_sp_netdev_ipip_type(const struct mlxsw_sp *mlxsw_sp,
				      const struct net_device *dev,
				      enum mlxsw_sp_ipip_type *p_type)
{
	struct mlxsw_sp_router *router = mlxsw_sp->router;
	const struct mlxsw_sp_ipip_ops *ipip_ops;
	enum mlxsw_sp_ipip_type ipipt;

	for (ipipt = 0; ipipt < MLXSW_SP_IPIP_TYPE_MAX; ++ipipt) {
		ipip_ops = router->ipip_ops_arr[ipipt];
		if (dev->type == ipip_ops->dev_type) {
			if (p_type)
				*p_type = ipipt;
			return true;
		}
	}
	return false;
}