#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_nexthop_group {int /*<<< orphan*/  nh_rif; int /*<<< orphan*/  adj_index_valid; } ;
struct mlxsw_sp_fib_entry {int type; TYPE_2__* fib_node; struct mlxsw_sp_nexthop_group* nh_group; } ;
struct TYPE_4__ {TYPE_1__* fib; } ;
struct TYPE_3__ {int proto; } ;

/* Variables and functions */
#define  MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE 134 
#define  MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP 133 
#define  MLXSW_SP_FIB_ENTRY_TYPE_LOCAL 132 
#define  MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP 131 
#define  MLXSW_SP_FIB_ENTRY_TYPE_REMOTE 130 
#define  MLXSW_SP_L3_PROTO_IPV4 129 
#define  MLXSW_SP_L3_PROTO_IPV6 128 
 int /*<<< orphan*/  mlxsw_sp_fib4_entry_should_offload (struct mlxsw_sp_fib_entry const*) ; 

__attribute__((used)) static bool
mlxsw_sp_fib_entry_should_offload(const struct mlxsw_sp_fib_entry *fib_entry)
{
	struct mlxsw_sp_nexthop_group *nh_group = fib_entry->nh_group;

	switch (fib_entry->fib_node->fib->proto) {
	case MLXSW_SP_L3_PROTO_IPV4:
		if (!mlxsw_sp_fib4_entry_should_offload(fib_entry))
			return false;
		break;
	case MLXSW_SP_L3_PROTO_IPV6:
		break;
	}

	switch (fib_entry->type) {
	case MLXSW_SP_FIB_ENTRY_TYPE_REMOTE:
		return !!nh_group->adj_index_valid;
	case MLXSW_SP_FIB_ENTRY_TYPE_LOCAL:
		return !!nh_group->nh_rif;
	case MLXSW_SP_FIB_ENTRY_TYPE_BLACKHOLE:
	case MLXSW_SP_FIB_ENTRY_TYPE_IPIP_DECAP:
	case MLXSW_SP_FIB_ENTRY_TYPE_NVE_DECAP:
		return true;
	default:
		return false;
	}
}