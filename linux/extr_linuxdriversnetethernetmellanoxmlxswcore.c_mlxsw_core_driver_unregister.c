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
struct mlxsw_driver {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_driver_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void mlxsw_core_driver_unregister(struct mlxsw_driver *mlxsw_driver)
{
	spin_lock(&mlxsw_core_driver_list_lock);
	list_del(&mlxsw_driver->list);
	spin_unlock(&mlxsw_core_driver_list_lock);
}