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
struct esw_mc_addr {scalar_t__ uplink_rule; } ;
struct mlx5_eswitch {struct esw_mc_addr mc_promisc; } ;

/* Variables and functions */
 int /*<<< orphan*/  esw_destroy_legacy_table (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_eswitch_disable_pf_vf_vports (struct mlx5_eswitch*) ; 

__attribute__((used)) static void esw_legacy_disable(struct mlx5_eswitch *esw)
{
	struct esw_mc_addr *mc_promisc;

	mlx5_eswitch_disable_pf_vf_vports(esw);

	mc_promisc = &esw->mc_promisc;
	if (mc_promisc->uplink_rule)
		mlx5_del_flow_rules(mc_promisc->uplink_rule);

	esw_destroy_legacy_table(esw);
}