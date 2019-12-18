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
struct mlxsw_sp_rif {int /*<<< orphan*/  rif_index; int /*<<< orphan*/  mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_fid* mlxsw_sp_fid_rfid_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_fid *
mlxsw_sp_rif_subport_fid_get(struct mlxsw_sp_rif *rif,
			     struct netlink_ext_ack *extack)
{
	return mlxsw_sp_fid_rfid_get(rif->mlxsw_sp, rif->rif_index);
}