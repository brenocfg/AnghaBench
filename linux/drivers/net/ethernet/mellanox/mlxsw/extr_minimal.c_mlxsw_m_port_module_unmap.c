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
typedef  size_t u8 ;
struct mlxsw_m {int* module_to_port; } ;

/* Variables and functions */

__attribute__((used)) static void mlxsw_m_port_module_unmap(struct mlxsw_m *mlxsw_m, u8 module)
{
	mlxsw_m->module_to_port[module] = -1;
}