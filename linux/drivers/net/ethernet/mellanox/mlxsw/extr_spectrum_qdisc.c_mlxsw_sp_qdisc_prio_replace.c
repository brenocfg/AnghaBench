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
typedef  int u8 ;
struct tc_prio_qopt_offload_params {int bands; int* priomap; } ;
struct TYPE_4__ {int backlog; } ;
struct mlxsw_sp_qdisc {int prio_bitmap; TYPE_2__ stats_base; TYPE_1__* ops; } ;
struct mlxsw_sp_port {struct mlxsw_sp_qdisc* tclass_qdiscs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* clean_stats ) (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ;} ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLXSW_SP_PRIO_BAND_TO_TCLASS (int) ; 
 int mlxsw_sp_port_prio_tc_set (struct mlxsw_sp_port*,int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_qdisc_destroy (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_port*,struct mlxsw_sp_qdisc*) ; 

__attribute__((used)) static int
mlxsw_sp_qdisc_prio_replace(struct mlxsw_sp_port *mlxsw_sp_port,
			    struct mlxsw_sp_qdisc *mlxsw_sp_qdisc,
			    void *params)
{
	struct tc_prio_qopt_offload_params *p = params;
	struct mlxsw_sp_qdisc *child_qdisc;
	int tclass, i, band, backlog;
	u8 old_priomap;
	int err;

	for (band = 0; band < p->bands; band++) {
		tclass = MLXSW_SP_PRIO_BAND_TO_TCLASS(band);
		child_qdisc = &mlxsw_sp_port->tclass_qdiscs[tclass];
		old_priomap = child_qdisc->prio_bitmap;
		child_qdisc->prio_bitmap = 0;
		for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++) {
			if (p->priomap[i] == band) {
				child_qdisc->prio_bitmap |= BIT(i);
				if (BIT(i) & old_priomap)
					continue;
				err = mlxsw_sp_port_prio_tc_set(mlxsw_sp_port,
								i, tclass);
				if (err)
					return err;
			}
		}
		if (old_priomap != child_qdisc->prio_bitmap &&
		    child_qdisc->ops && child_qdisc->ops->clean_stats) {
			backlog = child_qdisc->stats_base.backlog;
			child_qdisc->ops->clean_stats(mlxsw_sp_port,
						      child_qdisc);
			child_qdisc->stats_base.backlog = backlog;
		}
	}
	for (; band < IEEE_8021QAZ_MAX_TCS; band++) {
		tclass = MLXSW_SP_PRIO_BAND_TO_TCLASS(band);
		child_qdisc = &mlxsw_sp_port->tclass_qdiscs[tclass];
		child_qdisc->prio_bitmap = 0;
		mlxsw_sp_qdisc_destroy(mlxsw_sp_port, child_qdisc);
	}
	return 0;
}