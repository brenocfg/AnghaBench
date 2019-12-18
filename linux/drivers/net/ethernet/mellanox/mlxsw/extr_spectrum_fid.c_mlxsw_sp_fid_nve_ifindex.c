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
struct mlxsw_sp_fid {int nve_ifindex; int /*<<< orphan*/  vni_valid; } ;

/* Variables and functions */
 int EINVAL ; 

int mlxsw_sp_fid_nve_ifindex(const struct mlxsw_sp_fid *fid, int *nve_ifindex)
{
	if (!fid->vni_valid)
		return -EINVAL;

	*nve_ifindex = fid->nve_ifindex;

	return 0;
}