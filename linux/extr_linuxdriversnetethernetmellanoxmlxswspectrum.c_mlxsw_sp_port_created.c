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
struct mlxsw_sp {int /*<<< orphan*/ ** ports; } ;

/* Variables and functions */

__attribute__((used)) static bool mlxsw_sp_port_created(struct mlxsw_sp *mlxsw_sp, u8 local_port)
{
	return mlxsw_sp->ports[local_port] != NULL;
}