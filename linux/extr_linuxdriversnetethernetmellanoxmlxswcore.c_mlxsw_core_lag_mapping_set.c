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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * mapping; } ;
struct mlxsw_core {TYPE_1__ lag; } ;

/* Variables and functions */
 int mlxsw_core_lag_mapping_index (struct mlxsw_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mlxsw_core_lag_mapping_set(struct mlxsw_core *mlxsw_core,
				u16 lag_id, u8 port_index, u8 local_port)
{
	int index = mlxsw_core_lag_mapping_index(mlxsw_core,
						 lag_id, port_index);

	mlxsw_core->lag.mapping[index] = local_port;
}