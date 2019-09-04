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
typedef  scalar_t__ u32 ;
struct mlxsw_sp_nexthop {int num_adj_entries; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int __mlxsw_sp_nexthop_ipip_update (struct mlxsw_sp*,scalar_t__,struct mlxsw_sp_nexthop*) ; 

__attribute__((used)) static int mlxsw_sp_nexthop_ipip_update(struct mlxsw_sp *mlxsw_sp,
					u32 adj_index,
					struct mlxsw_sp_nexthop *nh)
{
	int i;

	for (i = 0; i < nh->num_adj_entries; i++) {
		int err;

		err = __mlxsw_sp_nexthop_ipip_update(mlxsw_sp, adj_index + i,
						     nh);
		if (err)
			return err;
	}

	return 0;
}