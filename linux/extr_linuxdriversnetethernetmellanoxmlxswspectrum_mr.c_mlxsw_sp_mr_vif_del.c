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
typedef  size_t vifi_t ;
struct mlxsw_sp_mr_vif {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_mr_table {struct mlxsw_sp_mr_vif* vifs; } ;

/* Variables and functions */
 size_t MAXVIFS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_vif_unresolve (struct mlxsw_sp_mr_table*,int /*<<< orphan*/ *,struct mlxsw_sp_mr_vif*) ; 

void mlxsw_sp_mr_vif_del(struct mlxsw_sp_mr_table *mr_table, vifi_t vif_index)
{
	struct mlxsw_sp_mr_vif *mr_vif = &mr_table->vifs[vif_index];

	if (WARN_ON(vif_index >= MAXVIFS))
		return;
	if (WARN_ON(!mr_vif->dev))
		return;
	mlxsw_sp_mr_vif_unresolve(mr_table, NULL, mr_vif);
}