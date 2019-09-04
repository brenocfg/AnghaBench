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
struct mlxsw_sp_acl_tcam_pattern {int dummy; } ;
struct mlxsw_sp_acl_tcam_group {unsigned int patterns_count; int tmplt_elusage_set; int /*<<< orphan*/  id; int /*<<< orphan*/  chunk_ht; int /*<<< orphan*/  region_list; int /*<<< orphan*/  tmplt_elusage; struct mlxsw_sp_acl_tcam_pattern const* patterns; struct mlxsw_sp_acl_tcam* tcam; } ;
struct mlxsw_sp_acl_tcam {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlxsw_afk_element_usage*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_chunk_ht_params ; 
 int mlxsw_sp_acl_tcam_group_id_get (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_group_id_put (struct mlxsw_sp_acl_tcam*,int /*<<< orphan*/ ) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_acl_tcam_group_add(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_tcam *tcam,
			    struct mlxsw_sp_acl_tcam_group *group,
			    const struct mlxsw_sp_acl_tcam_pattern *patterns,
			    unsigned int patterns_count,
			    struct mlxsw_afk_element_usage *tmplt_elusage)
{
	int err;

	group->tcam = tcam;
	group->patterns = patterns;
	group->patterns_count = patterns_count;
	if (tmplt_elusage) {
		group->tmplt_elusage_set = true;
		memcpy(&group->tmplt_elusage, tmplt_elusage,
		       sizeof(group->tmplt_elusage));
	}
	INIT_LIST_HEAD(&group->region_list);
	err = mlxsw_sp_acl_tcam_group_id_get(tcam, &group->id);
	if (err)
		return err;

	err = rhashtable_init(&group->chunk_ht,
			      &mlxsw_sp_acl_tcam_chunk_ht_params);
	if (err)
		goto err_rhashtable_init;

	return 0;

err_rhashtable_init:
	mlxsw_sp_acl_tcam_group_id_put(tcam, group->id);
	return err;
}