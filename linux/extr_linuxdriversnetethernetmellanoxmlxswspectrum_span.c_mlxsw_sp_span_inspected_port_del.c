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
struct mlxsw_sp_span_inspected_port {int /*<<< orphan*/  list; } ;
struct mlxsw_sp_span_entry {int dummy; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum mlxsw_sp_span_type { ____Placeholder_mlxsw_sp_span_type } mlxsw_sp_span_type ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBIB_LEN ; 
 int MLXSW_SP_SPAN_EGRESS ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_span_inspected_port*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_reg_sbib_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_span_inspected_port* mlxsw_sp_span_entry_bound_port_find (struct mlxsw_sp_span_entry*,int,struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_span_entry_put (struct mlxsw_sp*,struct mlxsw_sp_span_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_inspected_port_bind (struct mlxsw_sp_port*,struct mlxsw_sp_span_entry*,int,int) ; 
 int /*<<< orphan*/  sbib ; 

__attribute__((used)) static void
mlxsw_sp_span_inspected_port_del(struct mlxsw_sp_port *port,
				 struct mlxsw_sp_span_entry *span_entry,
				 enum mlxsw_sp_span_type type,
				 bool bind)
{
	struct mlxsw_sp_span_inspected_port *inspected_port;
	struct mlxsw_sp *mlxsw_sp = port->mlxsw_sp;
	char sbib_pl[MLXSW_REG_SBIB_LEN];

	inspected_port = mlxsw_sp_span_entry_bound_port_find(span_entry, type,
							     port, bind);
	if (!inspected_port)
		return;

	if (bind)
		mlxsw_sp_span_inspected_port_bind(port, span_entry, type,
						  false);
	/* remove the SBIB buffer if it was egress SPAN */
	if (type == MLXSW_SP_SPAN_EGRESS) {
		mlxsw_reg_sbib_pack(sbib_pl, port->local_port, 0);
		mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbib), sbib_pl);
	}

	mlxsw_sp_span_entry_put(mlxsw_sp, span_entry);

	list_del(&inspected_port->list);
	kfree(inspected_port);
}