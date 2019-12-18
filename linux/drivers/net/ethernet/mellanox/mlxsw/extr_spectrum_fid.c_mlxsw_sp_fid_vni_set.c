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
struct mlxsw_sp_fid_ops {int (* vni_set ) (struct mlxsw_sp_fid*,int /*<<< orphan*/ ) ;} ;
struct mlxsw_sp_fid_family {struct mlxsw_sp* mlxsw_sp; struct mlxsw_sp_fid_ops* ops; } ;
struct mlxsw_sp_fid {int vni_valid; int nve_type; int nve_ifindex; int /*<<< orphan*/  vni_ht_node; int /*<<< orphan*/  vni; struct mlxsw_sp_fid_family* fid_family; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
typedef  enum mlxsw_sp_nve_type { ____Placeholder_mlxsw_sp_nve_type } mlxsw_sp_nve_type ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  vni_ht; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_vni_ht_params ; 
 int rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp_fid*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_fid_vni_set(struct mlxsw_sp_fid *fid, enum mlxsw_sp_nve_type type,
			 __be32 vni, int nve_ifindex)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;
	const struct mlxsw_sp_fid_ops *ops = fid_family->ops;
	struct mlxsw_sp *mlxsw_sp = fid_family->mlxsw_sp;
	int err;

	if (WARN_ON(!ops->vni_set || fid->vni_valid))
		return -EINVAL;

	fid->nve_type = type;
	fid->nve_ifindex = nve_ifindex;
	fid->vni = vni;
	err = rhashtable_lookup_insert_fast(&mlxsw_sp->fid_core->vni_ht,
					    &fid->vni_ht_node,
					    mlxsw_sp_fid_vni_ht_params);
	if (err)
		return err;

	err = ops->vni_set(fid, vni);
	if (err)
		goto err_vni_set;

	fid->vni_valid = true;

	return 0;

err_vni_set:
	rhashtable_remove_fast(&mlxsw_sp->fid_core->vni_ht, &fid->vni_ht_node,
			       mlxsw_sp_fid_vni_ht_params);
	return err;
}