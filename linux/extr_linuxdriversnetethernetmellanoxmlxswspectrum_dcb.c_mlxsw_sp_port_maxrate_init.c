#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* maxrate; } ;
struct mlxsw_sp_port {TYPE_1__ dcb; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tc_maxrate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG_QEEC_MAS_DIS ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_maxrate_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	int i;

	mlxsw_sp_port->dcb.maxrate = kmalloc(sizeof(*mlxsw_sp_port->dcb.maxrate),
					     GFP_KERNEL);
	if (!mlxsw_sp_port->dcb.maxrate)
		return -ENOMEM;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		mlxsw_sp_port->dcb.maxrate->tc_maxrate[i] = MLXSW_REG_QEEC_MAS_DIS;

	return 0;
}