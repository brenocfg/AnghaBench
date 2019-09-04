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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_device {TYPE_1__* dev; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct mlxsw_sp_fid* mlxsw_sp_fid_8021d_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (TYPE_1__*) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_bridge_8021d_fid_get(struct mlxsw_sp_bridge_device *bridge_device,
			      u16 vid)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);

	return mlxsw_sp_fid_8021d_get(mlxsw_sp, bridge_device->dev->ifindex);
}