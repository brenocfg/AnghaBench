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
struct mlx5_vport {int /*<<< orphan*/ * promisc_rule; int /*<<< orphan*/  vport; int /*<<< orphan*/ * allmulti_rule; } ;
struct esw_mc_addr {scalar_t__ refcnt; int /*<<< orphan*/ * uplink_rule; } ;
struct mlx5_eswitch {struct esw_mc_addr mc_promisc; } ;

/* Variables and functions */
 int IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_VPORT_UPLINK ; 
 void* esw_fdb_set_vport_allmulti_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * esw_fdb_set_vport_promisc_rule (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esw_apply_vport_rx_mode(struct mlx5_eswitch *esw,
				    struct mlx5_vport *vport,
				    bool promisc, bool mc_promisc)
{
	struct esw_mc_addr *allmulti_addr = &esw->mc_promisc;

	if (IS_ERR_OR_NULL(vport->allmulti_rule) != mc_promisc)
		goto promisc;

	if (mc_promisc) {
		vport->allmulti_rule =
			esw_fdb_set_vport_allmulti_rule(esw, vport->vport);
		if (!allmulti_addr->uplink_rule)
			allmulti_addr->uplink_rule =
				esw_fdb_set_vport_allmulti_rule(esw,
								MLX5_VPORT_UPLINK);
		allmulti_addr->refcnt++;
	} else if (vport->allmulti_rule) {
		mlx5_del_flow_rules(vport->allmulti_rule);
		vport->allmulti_rule = NULL;

		if (--allmulti_addr->refcnt > 0)
			goto promisc;

		if (allmulti_addr->uplink_rule)
			mlx5_del_flow_rules(allmulti_addr->uplink_rule);
		allmulti_addr->uplink_rule = NULL;
	}

promisc:
	if (IS_ERR_OR_NULL(vport->promisc_rule) != promisc)
		return;

	if (promisc) {
		vport->promisc_rule =
			esw_fdb_set_vport_promisc_rule(esw, vport->vport);
	} else if (vport->promisc_rule) {
		mlx5_del_flow_rules(vport->promisc_rule);
		vport->promisc_rule = NULL;
	}
}