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
struct mlxsw_sp_port {TYPE_1__* sample; } ;
struct TYPE_2__ {int /*<<< orphan*/  psample_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_sample_set (struct mlxsw_sp_port*,int,int) ; 

__attribute__((used)) static void
mlxsw_sp_port_del_cls_matchall_sample(struct mlxsw_sp_port *mlxsw_sp_port)
{
	if (!mlxsw_sp_port->sample)
		return;

	mlxsw_sp_port_sample_set(mlxsw_sp_port, false, 1);
	RCU_INIT_POINTER(mlxsw_sp_port->sample->psample_group, NULL);
}