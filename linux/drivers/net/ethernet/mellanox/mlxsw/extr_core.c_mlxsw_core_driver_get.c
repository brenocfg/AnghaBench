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
struct mlxsw_driver {int dummy; } ;

/* Variables and functions */
 struct mlxsw_driver* __driver_find (char const*) ; 
 int /*<<< orphan*/  mlxsw_core_driver_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_driver *mlxsw_core_driver_get(const char *kind)
{
	struct mlxsw_driver *mlxsw_driver;

	spin_lock(&mlxsw_core_driver_list_lock);
	mlxsw_driver = __driver_find(kind);
	spin_unlock(&mlxsw_core_driver_list_lock);
	return mlxsw_driver;
}