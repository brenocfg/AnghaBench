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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;
struct mlxsw_sp_acl_tcam_mr_ruleset {TYPE_1__ vgroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16
mlxsw_sp_acl_tcam_mr_ruleset_group_id(void *ruleset_priv)
{
	struct mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;

	return mlxsw_sp_acl_tcam_group_id(&ruleset->vgroup.group);
}