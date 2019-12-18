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
struct mlxsw_sp {TYPE_1__* router; } ;
struct TYPE_2__ {int /*<<< orphan*/  inetaddr_nb; int /*<<< orphan*/  inet6addr_nb; int /*<<< orphan*/  nexthop_ht; int /*<<< orphan*/  nexthop_group_ht; int /*<<< orphan*/  netevent_nb; int /*<<< orphan*/  fib_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_router_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mlxsw_sp_ipips_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_neigh_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_rifs_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_vrs_fini (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_fib_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netevent_notifier (int /*<<< orphan*/ *) ; 

void mlxsw_sp_router_fini(struct mlxsw_sp *mlxsw_sp)
{
	unregister_fib_notifier(&mlxsw_sp->router->fib_nb);
	unregister_netevent_notifier(&mlxsw_sp->router->netevent_nb);
	mlxsw_sp_neigh_fini(mlxsw_sp);
	mlxsw_sp_vrs_fini(mlxsw_sp);
	mlxsw_sp_mr_fini(mlxsw_sp);
	mlxsw_sp_lpm_fini(mlxsw_sp);
	rhashtable_destroy(&mlxsw_sp->router->nexthop_group_ht);
	rhashtable_destroy(&mlxsw_sp->router->nexthop_ht);
	mlxsw_sp_ipips_fini(mlxsw_sp);
	mlxsw_sp_rifs_fini(mlxsw_sp);
	__mlxsw_sp_router_fini(mlxsw_sp);
	unregister_inet6addr_notifier(&mlxsw_sp->router->inet6addr_nb);
	unregister_inetaddr_notifier(&mlxsw_sp->router->inetaddr_nb);
	kfree(mlxsw_sp->router);
}