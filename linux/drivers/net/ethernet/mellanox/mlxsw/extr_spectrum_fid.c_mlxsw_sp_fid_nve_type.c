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
struct mlxsw_sp_fid {int nve_type; int /*<<< orphan*/  vni_valid; } ;
typedef  enum mlxsw_sp_nve_type { ____Placeholder_mlxsw_sp_nve_type } mlxsw_sp_nve_type ;

/* Variables and functions */
 int EINVAL ; 

int mlxsw_sp_fid_nve_type(const struct mlxsw_sp_fid *fid,
			  enum mlxsw_sp_nve_type *p_type)
{
	if (!fid->vni_valid)
		return -EINVAL;

	*p_type = fid->nve_type;

	return 0;
}