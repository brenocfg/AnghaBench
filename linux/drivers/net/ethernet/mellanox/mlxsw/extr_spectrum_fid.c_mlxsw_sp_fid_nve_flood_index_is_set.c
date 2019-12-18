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
struct mlxsw_sp_fid {int nve_flood_index_valid; } ;

/* Variables and functions */

bool mlxsw_sp_fid_nve_flood_index_is_set(const struct mlxsw_sp_fid *fid)
{
	return fid->nve_flood_index_valid;
}