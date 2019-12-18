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
struct mlxsw_sp_mr_route_vif_entry {int /*<<< orphan*/  vif_node; int /*<<< orphan*/  route_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mr_route_vif_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_mr_route_evif_unlink(struct mlxsw_sp_mr_route_vif_entry *rve)
{
	list_del(&rve->route_node);
	list_del(&rve->vif_node);
	kfree(rve);
}