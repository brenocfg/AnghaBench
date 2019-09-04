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
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_FID_TYPE_DUMMY ; 
 struct mlxsw_sp_fid* mlxsw_sp_fid_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct mlxsw_sp_fid *mlxsw_sp_fid_dummy_get(struct mlxsw_sp *mlxsw_sp)
{
	return mlxsw_sp_fid_get(mlxsw_sp, MLXSW_SP_FID_TYPE_DUMMY, NULL);
}