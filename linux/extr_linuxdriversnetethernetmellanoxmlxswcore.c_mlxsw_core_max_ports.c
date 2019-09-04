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
struct mlxsw_core {unsigned int max_ports; } ;

/* Variables and functions */

unsigned int mlxsw_core_max_ports(const struct mlxsw_core *mlxsw_core)
{
	return mlxsw_core->max_ports;
}