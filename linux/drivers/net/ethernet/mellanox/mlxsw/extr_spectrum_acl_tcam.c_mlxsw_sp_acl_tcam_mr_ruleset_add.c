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
struct mlxsw_sp_acl_tcam_mr_ruleset {int /*<<< orphan*/  vgroup; int /*<<< orphan*/  vchunk; } ;
struct mlxsw_sp_acl_tcam {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_TCAM_PATTERNS_COUNT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_patterns ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_get (struct mlxsw_sp*,int /*<<< orphan*/ *,int,struct mlxsw_afk_element_usage*) ; 
 int mlxsw_sp_acl_tcam_vgroup_add (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlxsw_afk_element_usage*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vgroup_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_mr_ruleset_add(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_tcam *tcam,
				 void *ruleset_priv,
				 struct mlxsw_afk_element_usage *tmplt_elusage)
{
	struct mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;
	int err;

	err = mlxsw_sp_acl_tcam_vgroup_add(mlxsw_sp, tcam, &ruleset->vgroup,
					   mlxsw_sp_acl_tcam_patterns,
					   MLXSW_SP_ACL_TCAM_PATTERNS_COUNT,
					   tmplt_elusage, false);
	if (err)
		return err;

	/* For most of the TCAM clients it would make sense to take a tcam chunk
	 * only when the first rule is written. This is not the case for
	 * multicast router as it is required to bind the multicast router to a
	 * specific ACL Group ID which must exist in HW before multicast router
	 * is initialized.
	 */
	ruleset->vchunk = mlxsw_sp_acl_tcam_vchunk_get(mlxsw_sp,
						       &ruleset->vgroup, 1,
						       tmplt_elusage);
	if (IS_ERR(ruleset->vchunk)) {
		err = PTR_ERR(ruleset->vchunk);
		goto err_chunk_get;
	}

	return 0;

err_chunk_get:
	mlxsw_sp_acl_tcam_vgroup_del(&ruleset->vgroup);
	return err;
}