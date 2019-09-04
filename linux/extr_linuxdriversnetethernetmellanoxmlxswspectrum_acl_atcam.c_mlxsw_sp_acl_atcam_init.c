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
struct mlxsw_sp_acl_atcam {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_erps_init (struct mlxsw_sp*,struct mlxsw_sp_acl_atcam*) ; 

int mlxsw_sp_acl_atcam_init(struct mlxsw_sp *mlxsw_sp,
			    struct mlxsw_sp_acl_atcam *atcam)
{
	return mlxsw_sp_acl_erps_init(mlxsw_sp, atcam);
}