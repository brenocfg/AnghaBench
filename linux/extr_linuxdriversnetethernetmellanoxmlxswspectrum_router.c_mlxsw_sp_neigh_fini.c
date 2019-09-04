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
struct mlxsw_sp {TYPE_2__* router; } ;
struct TYPE_3__ {int /*<<< orphan*/  dw; } ;
struct TYPE_4__ {int /*<<< orphan*/  neigh_ht; int /*<<< orphan*/  nexthop_probe_dw; TYPE_1__ neighs_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_neigh_fini(struct mlxsw_sp *mlxsw_sp)
{
	cancel_delayed_work_sync(&mlxsw_sp->router->neighs_update.dw);
	cancel_delayed_work_sync(&mlxsw_sp->router->nexthop_probe_dw);
	rhashtable_destroy(&mlxsw_sp->router->neigh_ht);
}