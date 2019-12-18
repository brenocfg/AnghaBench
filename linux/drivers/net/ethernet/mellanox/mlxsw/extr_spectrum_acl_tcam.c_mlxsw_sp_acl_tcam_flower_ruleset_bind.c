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
struct mlxsw_sp_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;
struct mlxsw_sp_acl_tcam_flower_ruleset {TYPE_1__ vgroup; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_tcam_group_bind (struct mlxsw_sp*,int /*<<< orphan*/ *,struct mlxsw_sp_port*,int) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_flower_ruleset_bind(struct mlxsw_sp *mlxsw_sp,
				      void *ruleset_priv,
				      struct mlxsw_sp_port *mlxsw_sp_port,
				      bool ingress)
{
	struct mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	return mlxsw_sp_acl_tcam_group_bind(mlxsw_sp, &ruleset->vgroup.group,
					    mlxsw_sp_port, ingress);
}