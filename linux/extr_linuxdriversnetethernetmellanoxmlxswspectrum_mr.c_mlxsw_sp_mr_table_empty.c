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
struct mlxsw_sp_mr_table {int /*<<< orphan*/  route_list; TYPE_1__* vifs; } ;
struct TYPE_2__ {scalar_t__ dev; } ;

/* Variables and functions */
 int MAXVIFS ; 
 int list_empty (int /*<<< orphan*/ *) ; 

bool mlxsw_sp_mr_table_empty(const struct mlxsw_sp_mr_table *mr_table)
{
	int i;

	for (i = 0; i < MAXVIFS; i++)
		if (mr_table->vifs[i].dev)
			return false;
	return list_empty(&mr_table->route_list);
}