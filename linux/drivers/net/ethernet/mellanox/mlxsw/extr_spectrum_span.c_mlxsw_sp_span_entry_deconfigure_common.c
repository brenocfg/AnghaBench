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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {struct mlxsw_sp_port* dest_port; } ;
struct mlxsw_sp_span_entry {int id; TYPE_1__ parms; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_reg_mpat_span_type { ____Placeholder_mlxsw_reg_mpat_span_type } mlxsw_reg_mpat_span_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MPAT_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_mpat_pack (char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpat ; 

__attribute__((used)) static void
mlxsw_sp_span_entry_deconfigure_common(struct mlxsw_sp_span_entry *span_entry,
				       enum mlxsw_reg_mpat_span_type span_type)
{
	struct mlxsw_sp_port *dest_port = span_entry->parms.dest_port;
	struct mlxsw_sp *mlxsw_sp = dest_port->mlxsw_sp;
	u8 local_port = dest_port->local_port;
	char mpat_pl[MLXSW_REG_MPAT_LEN];
	int pa_id = span_entry->id;

	mlxsw_reg_mpat_pack(mpat_pl, pa_id, local_port, false, span_type);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mpat), mpat_pl);
}