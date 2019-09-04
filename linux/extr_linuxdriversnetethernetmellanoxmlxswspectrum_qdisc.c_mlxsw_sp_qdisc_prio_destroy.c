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
struct mlxsw_sp_qdisc {int dummy; } ;
struct mlxsw_sp_port {TYPE_1__* tclass_qdiscs; } ;
struct TYPE_2__ {scalar_t__ prio_bitmap; } ;

/* Variables and functions */
 int IEEE_8021QAZ_MAX_TCS ; 
 int /*<<< orphan*/  MLXSW_SP_PORT_DEFAULT_TCLASS ; 
 int /*<<< orphan*/  mlxsw_sp_port_prio_tc_set (struct mlxsw_sp_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_qdisc_destroy (struct mlxsw_sp_port*,TYPE_1__*) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_prio_destroy(struct mlxsw_sp_port *mlxsw_sp_port,
			    struct mlxsw_sp_qdisc *mlxsw_sp_qdisc)
{
	int i;

	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
		mlxsw_sp_port_prio_tc_set(mlxsw_sp_port, i,
					  MLXSW_SP_PORT_DEFAULT_TCLASS);
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port,
				       &mlxsw_sp_port->tclass_qdiscs[i]);
		mlxsw_sp_port->tclass_qdiscs[i].prio_bitmap = 0;
	}

	return 0;
}