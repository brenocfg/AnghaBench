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
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp {TYPE_1__* acl; } ;
struct TYPE_2__ {struct mlxsw_sp_fid* dummy_fid; } ;

/* Variables and functions */

struct mlxsw_sp_fid *mlxsw_sp_acl_dummy_fid(struct mlxsw_sp *mlxsw_sp)
{
	return mlxsw_sp->acl->dummy_fid;
}