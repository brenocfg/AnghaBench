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
struct tc_prio_qopt_offload {int command; int /*<<< orphan*/  graft_params; int /*<<< orphan*/  stats; int /*<<< orphan*/  handle; int /*<<< orphan*/  replace_params; int /*<<< orphan*/  parent; } ;
struct mlxsw_sp_qdisc {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLXSW_SP_QDISC_PRIO ; 
#define  TC_PRIO_DESTROY 130 
#define  TC_PRIO_GRAFT 129 
 int TC_PRIO_REPLACE ; 
#define  TC_PRIO_STATS 128 
 int /*<<< orphan*/  mlxsw_sp_qdisc_compare (struct mlxsw_sp_qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_qdisc_destroy (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 
 struct mlxsw_sp_qdisc* mlxsw_sp_qdisc_find (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_qdisc_get_stats (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_qdisc_ops_prio ; 
 int mlxsw_sp_qdisc_prio_graft (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_qdisc_replace (struct mlxsw_sp_port*,int /*<<< orphan*/ ,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_sp_setup_tc_prio(struct mlxsw_sp_port *mlxsw_sp_port,
			   struct tc_prio_qopt_offload *p)
{
	struct mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, true);
	if (!mlxsw_sp_qdisc)
		return -EOPNOTSUPP;

	if (p->command == TC_PRIO_REPLACE)
		return mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_prio,
					      &p->replace_params);

	if (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle,
				    MLXSW_SP_QDISC_PRIO))
		return -EOPNOTSUPP;

	switch (p->command) {
	case TC_PRIO_DESTROY:
		return mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	case TC_PRIO_STATS:
		return mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	case TC_PRIO_GRAFT:
		return mlxsw_sp_qdisc_prio_graft(mlxsw_sp_port, mlxsw_sp_qdisc,
						 &p->graft_params);
	default:
		return -EOPNOTSUPP;
	}
}