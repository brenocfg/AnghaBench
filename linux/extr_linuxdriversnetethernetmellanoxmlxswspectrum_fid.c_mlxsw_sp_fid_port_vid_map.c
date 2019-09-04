#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_fid {TYPE_2__* fid_family; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* port_vid_map ) (struct mlxsw_sp_fid*,struct mlxsw_sp_port*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int stub1 (struct mlxsw_sp_fid*,struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_fid_port_vid_map(struct mlxsw_sp_fid *fid,
			      struct mlxsw_sp_port *mlxsw_sp_port, u16 vid)
{
	if (WARN_ON(!fid->fid_family->ops->port_vid_map))
		return -EINVAL;
	return fid->fid_family->ops->port_vid_map(fid, mlxsw_sp_port, vid);
}