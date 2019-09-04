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
struct tc_red_qopt_offload {int command; int /*<<< orphan*/  stats; int /*<<< orphan*/  xstats; int /*<<< orphan*/  handle; int /*<<< orphan*/  set; int /*<<< orphan*/  parent; } ;
struct mlxsw_sp_qdisc {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLXSW_SP_QDISC_RED ; 
#define  TC_RED_DESTROY 130 
 int TC_RED_REPLACE ; 
#define  TC_RED_STATS 129 
#define  TC_RED_XSTATS 128 
 int /*<<< orphan*/  mlxsw_sp_qdisc_compare (struct mlxsw_sp_qdisc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_qdisc_destroy (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 
 struct mlxsw_sp_qdisc* mlxsw_sp_qdisc_find (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_qdisc_get_stats (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_qdisc_get_xstats (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_qdisc_ops_red ; 
 int mlxsw_sp_qdisc_replace (struct mlxsw_sp_port*,int /*<<< orphan*/ ,struct mlxsw_sp_qdisc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_sp_setup_tc_red(struct mlxsw_sp_port *mlxsw_sp_port,
			  struct tc_red_qopt_offload *p)
{
	struct mlxsw_sp_qdisc *mlxsw_sp_qdisc;

	mlxsw_sp_qdisc = mlxsw_sp_qdisc_find(mlxsw_sp_port, p->parent, false);
	if (!mlxsw_sp_qdisc)
		return -EOPNOTSUPP;

	if (p->command == TC_RED_REPLACE)
		return mlxsw_sp_qdisc_replace(mlxsw_sp_port, p->handle,
					      mlxsw_sp_qdisc,
					      &mlxsw_sp_qdisc_ops_red,
					      &p->set);

	if (!mlxsw_sp_qdisc_compare(mlxsw_sp_qdisc, p->handle,
				    MLXSW_SP_QDISC_RED))
		return -EOPNOTSUPP;

	switch (p->command) {
	case TC_RED_DESTROY:
		return mlxsw_sp_qdisc_destroy(mlxsw_sp_port, mlxsw_sp_qdisc);
	case TC_RED_XSTATS:
		return mlxsw_sp_qdisc_get_xstats(mlxsw_sp_port, mlxsw_sp_qdisc,
						 p->xstats);
	case TC_RED_STATS:
		return mlxsw_sp_qdisc_get_stats(mlxsw_sp_port, mlxsw_sp_qdisc,
						&p->stats);
	default:
		return -EOPNOTSUPP;
	}
}