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
struct TYPE_2__ {int /*<<< orphan*/ * modify_metadata_rule; int /*<<< orphan*/  modify_metadata; } ;
struct mlx5_vport {TYPE_1__ ingress; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_modify_header_dealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void esw_vport_del_ingress_acl_modify_metadata(struct mlx5_eswitch *esw,
					       struct mlx5_vport *vport)
{
	if (vport->ingress.modify_metadata_rule) {
		mlx5_del_flow_rules(vport->ingress.modify_metadata_rule);
		mlx5_modify_header_dealloc(esw->dev, vport->ingress.modify_metadata);

		vport->ingress.modify_metadata_rule = NULL;
	}
}