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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_core_port_fini (struct mlxsw_core*,int /*<<< orphan*/ ) ; 

void mlxsw_core_port_fini(struct mlxsw_core *mlxsw_core, u8 local_port)
{
	__mlxsw_core_port_fini(mlxsw_core, local_port);
}