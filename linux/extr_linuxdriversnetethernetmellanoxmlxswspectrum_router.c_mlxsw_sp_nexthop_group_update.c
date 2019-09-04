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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; int /*<<< orphan*/  adj_index; } ;
struct mlxsw_sp_nexthop {int offloaded; int type; scalar_t__ num_adj_entries; scalar_t__ update; int /*<<< orphan*/  should_offload; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
#define  MLXSW_SP_NEXTHOP_TYPE_ETH 129 
#define  MLXSW_SP_NEXTHOP_TYPE_IPIP 128 
 int mlxsw_sp_nexthop_ipip_update (struct mlxsw_sp*,int /*<<< orphan*/ ,struct mlxsw_sp_nexthop*) ; 
 int mlxsw_sp_nexthop_update (struct mlxsw_sp*,int /*<<< orphan*/ ,struct mlxsw_sp_nexthop*) ; 

__attribute__((used)) static int
mlxsw_sp_nexthop_group_update(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_nexthop_group *nh_grp,
			      bool reallocate)
{
	u32 adj_index = nh_grp->adj_index; /* base */
	struct mlxsw_sp_nexthop *nh;
	int i;
	int err;

	for (i = 0; i < nh_grp->count; i++) {
		nh = &nh_grp->nexthops[i];

		if (!nh->should_offload) {
			nh->offloaded = 0;
			continue;
		}

		if (nh->update || reallocate) {
			switch (nh->type) {
			case MLXSW_SP_NEXTHOP_TYPE_ETH:
				err = mlxsw_sp_nexthop_update
					    (mlxsw_sp, adj_index, nh);
				break;
			case MLXSW_SP_NEXTHOP_TYPE_IPIP:
				err = mlxsw_sp_nexthop_ipip_update
					    (mlxsw_sp, adj_index, nh);
				break;
			}
			if (err)
				return err;
			nh->update = 0;
			nh->offloaded = 1;
		}
		adj_index += nh->num_adj_entries;
	}
	return 0;
}