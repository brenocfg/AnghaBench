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
struct mlxsw_sp_span_entry {int id; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;
typedef  enum mlxsw_reg_mpar_i_e { ____Placeholder_mlxsw_reg_mpar_i_e } mlxsw_reg_mpar_i_e ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MPAR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_mpar_pack (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpar ; 

__attribute__((used)) static int
mlxsw_sp_span_inspected_port_bind(struct mlxsw_sp_port *port,
				  struct mlxsw_sp_span_entry *span_entry,
				  enum mlxsw_sp_span_type type,
				  bool bind)
{
	struct mlxsw_sp *mlxsw_sp = port->mlxsw_sp;
	char mpar_pl[MLXSW_REG_MPAR_LEN];
	int pa_id = span_entry->id;

	/* bind the port to the SPAN entry */
	mlxsw_reg_mpar_pack(mpar_pl, port->local_port,
			    (enum mlxsw_reg_mpar_i_e)type, bind, pa_id);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mpar), mpar_pl);
}