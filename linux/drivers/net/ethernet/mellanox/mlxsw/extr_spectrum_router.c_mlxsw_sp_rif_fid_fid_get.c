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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_rif {int /*<<< orphan*/  dev; int /*<<< orphan*/  mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_fid* mlxsw_sp_bridge_fid_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_rif_fid_fid_get(struct mlxsw_sp_rif *rif,
			 struct netlink_ext_ack *extack)
{
	return mlxsw_sp_bridge_fid_get(rif->mlxsw_sp, rif->dev, 0, extack);
}