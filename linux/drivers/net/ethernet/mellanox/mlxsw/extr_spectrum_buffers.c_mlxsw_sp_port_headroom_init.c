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
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_port_pb_init (struct mlxsw_sp_port*) ; 
 int mlxsw_sp_port_pb_prio_init (struct mlxsw_sp_port*) ; 

__attribute__((used)) static int mlxsw_sp_port_headroom_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	int err;

	err = mlxsw_sp_port_pb_init(mlxsw_sp_port);
	if (err)
		return err;
	return mlxsw_sp_port_pb_prio_init(mlxsw_sp_port);
}