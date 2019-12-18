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
struct mlxsw_sp_acl_tcam_mr_rule {int /*<<< orphan*/  ventry; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_ventry_del (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_mr_rule_del(struct mlxsw_sp *mlxsw_sp, void *rule_priv)
{
	struct mlxsw_sp_acl_tcam_mr_rule *rule = rule_priv;

	mlxsw_sp_acl_tcam_ventry_del(mlxsw_sp, &rule->ventry);
}