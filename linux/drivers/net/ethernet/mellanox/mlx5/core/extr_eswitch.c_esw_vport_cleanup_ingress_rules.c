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
struct TYPE_2__ {int /*<<< orphan*/ * allow_rule; int /*<<< orphan*/ * drop_rule; } ;
struct mlx5_vport {TYPE_1__ ingress; } ;
struct mlx5_eswitch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_vport_del_ingress_acl_modify_metadata (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 

void esw_vport_cleanup_ingress_rules(struct mlx5_eswitch *esw,
				     struct mlx5_vport *vport)
{
	if (!IS_ERR_OR_NULL(vport->ingress.drop_rule))
		mlx5_del_flow_rules(vport->ingress.drop_rule);

	if (!IS_ERR_OR_NULL(vport->ingress.allow_rule))
		mlx5_del_flow_rules(vport->ingress.allow_rule);

	vport->ingress.drop_rule = NULL;
	vport->ingress.allow_rule = NULL;

	esw_vport_del_ingress_acl_modify_metadata(esw, vport);
}