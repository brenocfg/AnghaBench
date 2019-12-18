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
struct mlxsw_sp_nexthop_group {int count; struct mlxsw_sp_nexthop* nexthops; int /*<<< orphan*/  fib_list; } ;
struct TYPE_3__ {TYPE_2__* fib_nh; } ;
struct mlxsw_sp_nexthop {TYPE_1__ key; } ;
struct mlxsw_sp_fib_entry {struct mlxsw_sp_nexthop_group* nh_group; } ;
struct TYPE_4__ {int /*<<< orphan*/  fib_nh_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTNH_F_OFFLOAD ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_fib4_entry_offload_unset(struct mlxsw_sp_fib_entry *fib_entry)
{
	struct mlxsw_sp_nexthop_group *nh_grp = fib_entry->nh_group;
	int i;

	if (!list_is_singular(&nh_grp->fib_list))
		return;

	for (i = 0; i < nh_grp->count; i++) {
		struct mlxsw_sp_nexthop *nh = &nh_grp->nexthops[i];

		nh->key.fib_nh->fib_nh_flags &= ~RTNH_F_OFFLOAD;
	}
}