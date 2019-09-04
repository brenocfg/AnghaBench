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
struct net_device {int dummy; } ;
struct mlxsw_sp_mr_vif {struct net_device const* dev; } ;
struct mlxsw_sp_mr_table {struct mlxsw_sp_mr_vif* vifs; } ;

/* Variables and functions */
 size_t MAXVIFS ; 

__attribute__((used)) static struct mlxsw_sp_mr_vif *
mlxsw_sp_mr_dev_vif_lookup(struct mlxsw_sp_mr_table *mr_table,
			   const struct net_device *dev)
{
	vifi_t vif_index;

	for (vif_index = 0; vif_index < MAXVIFS; vif_index++)
		if (mr_table->vifs[vif_index].dev == dev)
			return &mr_table->vifs[vif_index];
	return NULL;
}