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
struct TYPE_2__ {int /*<<< orphan*/ * allow_untagged_spoofchk_grp; int /*<<< orphan*/ * allow_untagged_only_grp; int /*<<< orphan*/ * allow_spoofchk_only_grp; int /*<<< orphan*/ * drop_grp; int /*<<< orphan*/ * acl; } ;
struct mlx5_vport {TYPE_1__ ingress; int /*<<< orphan*/  vport; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_vport_cleanup_ingress_rules (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 

void esw_vport_disable_ingress_acl(struct mlx5_eswitch *esw,
				   struct mlx5_vport *vport)
{
	if (IS_ERR_OR_NULL(vport->ingress.acl))
		return;

	esw_debug(esw->dev, "Destroy vport[%d] E-Switch ingress ACL\n", vport->vport);

	esw_vport_cleanup_ingress_rules(esw, vport);
	mlx5_destroy_flow_group(vport->ingress.allow_spoofchk_only_grp);
	mlx5_destroy_flow_group(vport->ingress.allow_untagged_only_grp);
	mlx5_destroy_flow_group(vport->ingress.allow_untagged_spoofchk_grp);
	mlx5_destroy_flow_group(vport->ingress.drop_grp);
	mlx5_destroy_flow_table(vport->ingress.acl);
	vport->ingress.acl = NULL;
	vport->ingress.drop_grp = NULL;
	vport->ingress.allow_spoofchk_only_grp = NULL;
	vport->ingress.allow_untagged_only_grp = NULL;
	vport->ingress.allow_untagged_spoofchk_grp = NULL;
}