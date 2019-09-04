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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sib_port {int /*<<< orphan*/  local_port; struct mlxsw_sib* mlxsw_sib; } ;
struct mlxsw_sib {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_ib_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptys ; 

__attribute__((used)) static int mlxsw_sib_port_speed_set(struct mlxsw_sib_port *mlxsw_sib_port,
				    u16 speed, u16 width)
{
	struct mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	char ptys_pl[MLXSW_REG_PTYS_LEN];

	mlxsw_reg_ptys_ib_pack(ptys_pl, mlxsw_sib_port->local_port, speed,
			       width);
	return mlxsw_reg_write(mlxsw_sib->core, MLXSW_REG(ptys), ptys_pl);
}