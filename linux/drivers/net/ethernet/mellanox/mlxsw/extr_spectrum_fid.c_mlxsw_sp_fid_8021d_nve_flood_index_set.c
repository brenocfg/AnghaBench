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
struct mlxsw_sp_fid_family {int /*<<< orphan*/  mlxsw_sp; } ;
struct mlxsw_sp_fid {int /*<<< orphan*/  vni_valid; int /*<<< orphan*/  vni; int /*<<< orphan*/  fid_index; struct mlxsw_sp_fid_family* fid_family; } ;

/* Variables and functions */
 int mlxsw_sp_fid_vni_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sp_fid_8021d_nve_flood_index_set(struct mlxsw_sp_fid *fid,
						  u32 nve_flood_index)
{
	struct mlxsw_sp_fid_family *fid_family = fid->fid_family;

	return mlxsw_sp_fid_vni_op(fid_family->mlxsw_sp, fid->fid_index,
				   fid->vni, fid->vni_valid, nve_flood_index,
				   true);
}