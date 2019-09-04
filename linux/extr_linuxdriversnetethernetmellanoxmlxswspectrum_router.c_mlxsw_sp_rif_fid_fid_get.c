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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_rif {TYPE_1__* dev; int /*<<< orphan*/  mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 struct mlxsw_sp_fid* mlxsw_sp_fid_8021d_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_rif_fid_fid_get(struct mlxsw_sp_rif *rif,
			 struct netlink_ext_ack *extack)
{
	return mlxsw_sp_fid_8021d_get(rif->mlxsw_sp, rif->dev->ifindex);
}