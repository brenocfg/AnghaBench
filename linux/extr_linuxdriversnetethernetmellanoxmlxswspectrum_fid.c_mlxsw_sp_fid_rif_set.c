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
struct mlxsw_sp_rif {int dummy; } ;
struct mlxsw_sp_fid {struct mlxsw_sp_rif* rif; } ;

/* Variables and functions */

void mlxsw_sp_fid_rif_set(struct mlxsw_sp_fid *fid, struct mlxsw_sp_rif *rif)
{
	fid->rif = rif;
}