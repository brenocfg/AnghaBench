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
struct mlxsw_thermal {int dummy; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_bus_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int mlxsw_thermal_init(struct mlxsw_core *mlxsw_core,
				     const struct mlxsw_bus_info *mlxsw_bus_info,
				     struct mlxsw_thermal **p_thermal)
{
	return 0;
}