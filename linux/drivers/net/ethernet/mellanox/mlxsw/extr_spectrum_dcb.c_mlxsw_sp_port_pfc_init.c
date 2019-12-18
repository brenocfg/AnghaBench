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
struct TYPE_3__ {TYPE_2__* pfc; } ;
struct mlxsw_sp_port {TYPE_1__ dcb; } ;
struct TYPE_4__ {int /*<<< orphan*/  pfc_cap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE_8021QAZ_MAX_TCS ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_port_pfc_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	mlxsw_sp_port->dcb.pfc = kzalloc(sizeof(*mlxsw_sp_port->dcb.pfc),
					 GFP_KERNEL);
	if (!mlxsw_sp_port->dcb.pfc)
		return -ENOMEM;

	mlxsw_sp_port->dcb.pfc->pfc_cap = IEEE_8021QAZ_MAX_TCS;

	return 0;
}