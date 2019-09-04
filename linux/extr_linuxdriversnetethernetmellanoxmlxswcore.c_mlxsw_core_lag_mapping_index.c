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
typedef  int u8 ;
typedef  int u16 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_LAG_MEMBERS ; 
 int MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_core_lag_mapping_index(struct mlxsw_core *mlxsw_core,
					u16 lag_id, u8 port_index)
{
	return MLXSW_CORE_RES_GET(mlxsw_core, MAX_LAG_MEMBERS) * lag_id +
	       port_index;
}