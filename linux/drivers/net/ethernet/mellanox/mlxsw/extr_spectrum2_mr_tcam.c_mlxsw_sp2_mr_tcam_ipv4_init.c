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
struct mlxsw_sp2_mr_tcam {int /*<<< orphan*/  ruleset4; int /*<<< orphan*/  mlxsw_sp; int /*<<< orphan*/  acl_block; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_PEMRBT_PROTO_IPV4 ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_PROFILE_MR ; 
 int /*<<< orphan*/  MLXSW_SP_L3_PROTO_IPV4 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afk_element_usage_fill (struct mlxsw_afk_element_usage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp2_mr_tcam_bind_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp2_mr_tcam_usage_ipv4 ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp2_mr_tcam_ipv4_init(struct mlxsw_sp2_mr_tcam *mr_tcam)
{
	struct mlxsw_afk_element_usage elusage;
	int err;

	/* Initialize IPv4 ACL group. */
	mlxsw_afk_element_usage_fill(&elusage,
				     mlxsw_sp2_mr_tcam_usage_ipv4,
				     ARRAY_SIZE(mlxsw_sp2_mr_tcam_usage_ipv4));
	mr_tcam->ruleset4 = mlxsw_sp_acl_ruleset_get(mr_tcam->mlxsw_sp,
						     mr_tcam->acl_block,
						     MLXSW_SP_L3_PROTO_IPV4,
						     MLXSW_SP_ACL_PROFILE_MR,
						     &elusage);

	if (IS_ERR(mr_tcam->ruleset4))
		return PTR_ERR(mr_tcam->ruleset4);

	/* MC Router groups should be bound before routes are inserted. */
	err = mlxsw_sp2_mr_tcam_bind_group(mr_tcam->mlxsw_sp,
					   MLXSW_REG_PEMRBT_PROTO_IPV4,
					   mr_tcam->ruleset4);
	if (err)
		goto err_bind_group;

	return 0;

err_bind_group:
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset4);
	return err;
}