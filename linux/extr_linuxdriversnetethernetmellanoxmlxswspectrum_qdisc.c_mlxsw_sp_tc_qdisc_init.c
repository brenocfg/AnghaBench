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
struct mlxsw_sp_qdisc {int prio_bitmap; int tclass_num; } ;
struct mlxsw_sp_port {struct mlxsw_sp_qdisc* root_qdisc; struct mlxsw_sp_qdisc* tclass_qdiscs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLXSW_SP_PORT_DEFAULT_TCLASS ; 
 struct mlxsw_sp_qdisc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_qdisc*) ; 
 struct mlxsw_sp_qdisc* kzalloc (int,int /*<<< orphan*/ ) ; 

int mlxsw_sp_tc_qdisc_init(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct mlxsw_sp_qdisc *mlxsw_sp_qdisc;
	int i;

	mlxsw_sp_qdisc = kzalloc(sizeof(*mlxsw_sp_qdisc), GFP_KERNEL);
	if (!mlxsw_sp_qdisc)
		goto err_root_qdisc_init;

	mlxsw_sp_port->root_qdisc = mlxsw_sp_qdisc;
	mlxsw_sp_port->root_qdisc->prio_bitmap = 0xff;
	mlxsw_sp_port->root_qdisc->tclass_num = MLXSW_SP_PORT_DEFAULT_TCLASS;

	mlxsw_sp_qdisc = kcalloc(IEEE_8021QAZ_MAX_TCS,
				 sizeof(*mlxsw_sp_qdisc),
				 GFP_KERNEL);
	if (!mlxsw_sp_qdisc)
		goto err_tclass_qdiscs_init;

	mlxsw_sp_port->tclass_qdiscs = mlxsw_sp_qdisc;
	for (i = 0; i < IEEE_8021QAZ_MAX_TCS; i++)
		mlxsw_sp_port->tclass_qdiscs[i].tclass_num = i;

	return 0;

err_tclass_qdiscs_init:
	kfree(mlxsw_sp_port->root_qdisc);
err_root_qdisc_init:
	return -ENOMEM;
}