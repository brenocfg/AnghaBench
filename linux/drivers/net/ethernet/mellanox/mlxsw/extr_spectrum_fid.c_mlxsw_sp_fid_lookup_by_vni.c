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
struct mlxsw_sp_fid {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp {TYPE_1__* fid_core; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  vni_ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fid_vni_ht_params ; 
 struct mlxsw_sp_fid* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_fid *mlxsw_sp_fid_lookup_by_vni(struct mlxsw_sp *mlxsw_sp,
						__be32 vni)
{
	struct mlxsw_sp_fid *fid;

	fid = rhashtable_lookup_fast(&mlxsw_sp->fid_core->vni_ht, &vni,
				     mlxsw_sp_fid_vni_ht_params);
	if (fid)
		fid->ref_count++;

	return fid;
}