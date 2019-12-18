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
struct net_device {int dummy; } ;
struct mlxsw_sp_ipip_ops {scalar_t__ (* can_offload ) (struct mlxsw_sp*,struct net_device const*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp {TYPE_1__* router; } ;
typedef  enum mlxsw_sp_ipip_type { ____Placeholder_mlxsw_sp_ipip_type } mlxsw_sp_ipip_type ;
struct TYPE_2__ {struct mlxsw_sp_ipip_ops** ipip_ops_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV6 ; 
 scalar_t__ stub1 (struct mlxsw_sp*,struct net_device const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct mlxsw_sp*,struct net_device const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mlxsw_sp_netdevice_ipip_can_offload(struct mlxsw_sp *mlxsw_sp,
						const struct net_device *ol_dev,
						enum mlxsw_sp_ipip_type ipipt)
{
	const struct mlxsw_sp_ipip_ops *ops
		= mlxsw_sp->router->ipip_ops_arr[ipipt];

	/* For deciding whether decap should be offloaded, we don't care about
	 * overlay protocol, so ask whether either one is supported.
	 */
	return ops->can_offload(mlxsw_sp, ol_dev, MLXSW_SP_L3_PROTO_IPV4) ||
	       ops->can_offload(mlxsw_sp, ol_dev, MLXSW_SP_L3_PROTO_IPV6);
}