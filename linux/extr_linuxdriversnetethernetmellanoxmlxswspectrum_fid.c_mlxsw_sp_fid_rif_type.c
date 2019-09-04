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
struct mlxsw_sp_fid {TYPE_1__* fid_family; } ;
typedef  enum mlxsw_sp_rif_type { ____Placeholder_mlxsw_sp_rif_type } mlxsw_sp_rif_type ;
struct TYPE_2__ {int rif_type; } ;

/* Variables and functions */

enum mlxsw_sp_rif_type mlxsw_sp_fid_rif_type(const struct mlxsw_sp_fid *fid)
{
	return fid->fid_family->rif_type;
}