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
struct mlxsw_m {scalar_t__ max_ports; scalar_t__* module_to_port; } ;

/* Variables and functions */
 int mlxsw_m_port_module_info_get (struct mlxsw_m*,size_t,size_t*,size_t*) ; 

__attribute__((used)) static int mlxsw_m_port_module_map(struct mlxsw_m *mlxsw_m, u8 local_port,
				   u8 *last_module)
{
	u8 module, width;
	int err;

	/* Fill out to local port mapping array */
	err = mlxsw_m_port_module_info_get(mlxsw_m, local_port, &module,
					   &width);
	if (err)
		return err;

	if (!width)
		return 0;
	/* Skip, if port belongs to the cluster */
	if (module == *last_module)
		return 0;
	*last_module = module;
	mlxsw_m->module_to_port[module] = ++mlxsw_m->max_ports;

	return 0;
}