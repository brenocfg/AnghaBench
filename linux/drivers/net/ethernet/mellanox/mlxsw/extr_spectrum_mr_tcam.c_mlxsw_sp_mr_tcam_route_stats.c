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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp_mr_tcam_route {int /*<<< orphan*/  counter_index; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_flow_counter_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_mr_tcam_route_stats(struct mlxsw_sp *mlxsw_sp,
					void *route_priv, u64 *packets,
					u64 *bytes)
{
	struct mlxsw_sp_mr_tcam_route *route = route_priv;

	return mlxsw_sp_flow_counter_get(mlxsw_sp, route->counter_index,
					 packets, bytes);
}