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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_dpipe_table_adj_size (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static u64
mlxsw_sp_dpipe_table_adj_size_get(void *priv)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	u64 size;

	rtnl_lock();
	size = mlxsw_sp_dpipe_table_adj_size(mlxsw_sp);
	rtnl_unlock();

	return size;
}