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
typedef  size_t u16 ;
struct TYPE_4__ {int /*<<< orphan*/  gvmi; struct mlx5dr_cmd_vport_cap* vports_caps; } ;
struct TYPE_3__ {TYPE_2__ caps; } ;
struct mlx5dr_domain {TYPE_1__ info; int /*<<< orphan*/  mdev; } ;
struct mlx5dr_cmd_vport_cap {size_t num; int /*<<< orphan*/  vhca_gvmi; int /*<<< orphan*/  vport_gvmi; int /*<<< orphan*/  icm_address_tx; int /*<<< orphan*/  icm_address_rx; } ;

/* Variables and functions */
 int mlx5dr_cmd_query_esw_vport_context (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlx5dr_cmd_query_gvmi (int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_domain_query_vport(struct mlx5dr_domain *dmn,
				 bool other_vport,
				 u16 vport_number)
{
	struct mlx5dr_cmd_vport_cap *vport_caps;
	int ret;

	vport_caps = &dmn->info.caps.vports_caps[vport_number];

	ret = mlx5dr_cmd_query_esw_vport_context(dmn->mdev,
						 other_vport,
						 vport_number,
						 &vport_caps->icm_address_rx,
						 &vport_caps->icm_address_tx);
	if (ret)
		return ret;

	ret = mlx5dr_cmd_query_gvmi(dmn->mdev,
				    other_vport,
				    vport_number,
				    &vport_caps->vport_gvmi);
	if (ret)
		return ret;

	vport_caps->num = vport_number;
	vport_caps->vhca_gvmi = dmn->info.caps.gvmi;

	return 0;
}