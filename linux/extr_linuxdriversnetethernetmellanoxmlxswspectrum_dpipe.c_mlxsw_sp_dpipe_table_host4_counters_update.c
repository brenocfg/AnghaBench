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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  mlxsw_sp_dpipe_table_host_counters_update (struct mlxsw_sp*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_dpipe_table_host4_counters_update(void *priv, bool enable)
{
	struct mlxsw_sp *mlxsw_sp = priv;

	mlxsw_sp_dpipe_table_host_counters_update(mlxsw_sp, enable, AF_INET);
	return 0;
}