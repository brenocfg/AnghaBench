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
struct mlxsw_sp_nexthop_key {struct fib_nh* fib_nh; } ;
struct mlxsw_sp_nexthop {int /*<<< orphan*/  nh_grp; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct fib_nh {int dummy; } ;
struct TYPE_2__ {scalar_t__ aborted; } ;

/* Variables and functions */
#define  FIB_EVENT_NH_ADD 129 
#define  FIB_EVENT_NH_DEL 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_type_fini (struct mlxsw_sp*,struct mlxsw_sp_nexthop*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_type_init (struct mlxsw_sp*,struct mlxsw_sp_nexthop*,struct fib_nh*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop_group_refresh (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_nexthop* mlxsw_sp_nexthop_lookup (struct mlxsw_sp*,struct mlxsw_sp_nexthop_key) ; 

__attribute__((used)) static void mlxsw_sp_nexthop4_event(struct mlxsw_sp *mlxsw_sp,
				    unsigned long event, struct fib_nh *fib_nh)
{
	struct mlxsw_sp_nexthop_key key;
	struct mlxsw_sp_nexthop *nh;

	if (mlxsw_sp->router->aborted)
		return;

	key.fib_nh = fib_nh;
	nh = mlxsw_sp_nexthop_lookup(mlxsw_sp, key);
	if (WARN_ON_ONCE(!nh))
		return;

	switch (event) {
	case FIB_EVENT_NH_ADD:
		mlxsw_sp_nexthop4_type_init(mlxsw_sp, nh, fib_nh);
		break;
	case FIB_EVENT_NH_DEL:
		mlxsw_sp_nexthop4_type_fini(mlxsw_sp, nh);
		break;
	}

	mlxsw_sp_nexthop_group_refresh(mlxsw_sp, nh->nh_grp);
}