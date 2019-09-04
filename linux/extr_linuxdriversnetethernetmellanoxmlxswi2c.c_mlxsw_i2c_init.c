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
struct mlxsw_res {int dummy; } ;
struct mlxsw_i2c {struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;
struct mlxsw_config_profile {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
mlxsw_i2c_init(void *bus_priv, struct mlxsw_core *mlxsw_core,
	       const struct mlxsw_config_profile *profile,
	       struct mlxsw_res *resources)
{
	struct mlxsw_i2c *mlxsw_i2c = bus_priv;

	mlxsw_i2c->core = mlxsw_core;

	return 0;
}