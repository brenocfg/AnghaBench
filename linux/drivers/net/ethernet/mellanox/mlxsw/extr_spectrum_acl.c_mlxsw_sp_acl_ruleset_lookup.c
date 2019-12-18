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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_acl_ruleset {int dummy; } ;
struct mlxsw_sp_acl_profile_ops {int dummy; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp_acl {int dummy; } ;
struct mlxsw_sp {struct mlxsw_sp_acl* acl; } ;
typedef  enum mlxsw_sp_acl_profile { ____Placeholder_mlxsw_sp_acl_profile } mlxsw_sp_acl_profile ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 struct mlxsw_sp_acl_ruleset* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_ruleset* __mlxsw_sp_acl_ruleset_lookup (struct mlxsw_sp_acl*,struct mlxsw_sp_acl_block*,int /*<<< orphan*/ ,struct mlxsw_sp_acl_profile_ops const*) ; 
 struct mlxsw_sp_acl_profile_ops* mlxsw_sp_acl_tcam_profile_ops (struct mlxsw_sp*,int) ; 

struct mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_lookup(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_block *block, u32 chain_index,
			    enum mlxsw_sp_acl_profile profile)
{
	const struct mlxsw_sp_acl_profile_ops *ops;
	struct mlxsw_sp_acl *acl = mlxsw_sp->acl;
	struct mlxsw_sp_acl_ruleset *ruleset;

	ops = mlxsw_sp_acl_tcam_profile_ops(mlxsw_sp, profile);
	if (!ops)
		return ERR_PTR(-EINVAL);
	ruleset = __mlxsw_sp_acl_ruleset_lookup(acl, block, chain_index, ops);
	if (!ruleset)
		return ERR_PTR(-ENOENT);
	return ruleset;
}