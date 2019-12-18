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
struct mlxsw_sp_acl_tcam_vregion {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp_acl_tcam_vgroup {int dummy; } ;
struct mlxsw_sp {int dummy; } ;
struct mlxsw_afk_element_usage {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct mlxsw_sp_acl_tcam_vregion* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vgroup_use_patterns (struct mlxsw_sp_acl_tcam_vgroup*,struct mlxsw_afk_element_usage*,struct mlxsw_afk_element_usage*) ; 
 struct mlxsw_sp_acl_tcam_vregion* mlxsw_sp_acl_tcam_vgroup_vregion_find (struct mlxsw_sp_acl_tcam_vgroup*,unsigned int,struct mlxsw_afk_element_usage*,int*) ; 
 struct mlxsw_sp_acl_tcam_vregion* mlxsw_sp_acl_tcam_vregion_create (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vgroup*,unsigned int,struct mlxsw_afk_element_usage*) ; 

__attribute__((used)) static struct mlxsw_sp_acl_tcam_vregion *
mlxsw_sp_acl_tcam_vregion_get(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_acl_tcam_vgroup *vgroup,
			      unsigned int priority,
			      struct mlxsw_afk_element_usage *elusage)
{
	struct mlxsw_afk_element_usage vregion_elusage;
	struct mlxsw_sp_acl_tcam_vregion *vregion;
	bool need_split;

	vregion = mlxsw_sp_acl_tcam_vgroup_vregion_find(vgroup, priority,
							elusage, &need_split);
	if (vregion) {
		if (need_split) {
			/* According to priority, new vchunk should belong to
			 * an existing vregion. However, this vchunk needs
			 * elements that vregion does not contain. We need
			 * to split the existing vregion into two and create
			 * a new vregion for the new vchunk in between.
			 * This is not supported now.
			 */
			return ERR_PTR(-EOPNOTSUPP);
		}
		vregion->ref_count++;
		return vregion;
	}

	mlxsw_sp_acl_tcam_vgroup_use_patterns(vgroup, elusage,
					      &vregion_elusage);

	return mlxsw_sp_acl_tcam_vregion_create(mlxsw_sp, vgroup, priority,
						&vregion_elusage);
}