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
struct mlxsw_sp_acl_tcam_ventry {int /*<<< orphan*/  entry; struct mlxsw_sp_acl_tcam_vchunk* vchunk; } ;
struct mlxsw_sp_acl_tcam_vchunk {TYPE_1__* vregion; } ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  region; } ;

/* Variables and functions */
 int mlxsw_sp_acl_tcam_entry_action_replace (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_sp_acl_rule_info*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_ventry_action_replace(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_acl_tcam_ventry *ventry,
					struct mlxsw_sp_acl_rule_info *rulei)
{
	struct mlxsw_sp_acl_tcam_vchunk *vchunk = ventry->vchunk;

	return mlxsw_sp_acl_tcam_entry_action_replace(mlxsw_sp,
						      vchunk->vregion->region,
						      ventry->entry, rulei);
}