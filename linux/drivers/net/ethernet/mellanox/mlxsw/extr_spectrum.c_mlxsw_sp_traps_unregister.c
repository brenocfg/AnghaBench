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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct mlxsw_listener {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_core_trap_unregister (int /*<<< orphan*/ ,struct mlxsw_listener const*,struct mlxsw_sp*) ; 

__attribute__((used)) static void mlxsw_sp_traps_unregister(struct mlxsw_sp *mlxsw_sp,
				      const struct mlxsw_listener listeners[],
				      size_t listeners_count)
{
	int i;

	for (i = 0; i < listeners_count; i++) {
		mlxsw_core_trap_unregister(mlxsw_sp->core,
					   &listeners[i],
					   mlxsw_sp);
	}
}