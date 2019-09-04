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
struct mlxsw_sp_port {TYPE_1__* mlxsw_sp; int /*<<< orphan*/  local_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PPTB_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pptb_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pptb_prio_to_buff_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pptb ; 

__attribute__((used)) static int mlxsw_sp_port_pb_prio_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	char pptb_pl[MLXSW_REG_PPTB_LEN];
	int i;

	mlxsw_reg_pptb_pack(pptb_pl, mlxsw_sp_port->local_port);
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		mlxsw_reg_pptb_prio_to_buff_pack(pptb_pl, i, 0);
	return mlxsw_reg_write(mlxsw_sp_port->mlxsw_sp->core, MLXSW_REG(pptb),
			       pptb_pl);
}