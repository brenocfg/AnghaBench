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
typedef  scalar_t__ u16 ;
struct mlxsw_sp_port {scalar_t__ pvid; } ;

/* Variables and functions */

__attribute__((used)) static u16
mlxsw_sp_port_pvid_determine(const struct mlxsw_sp_port *mlxsw_sp_port,
			     u16 vid, bool is_pvid)
{
	if (is_pvid)
		return vid;
	else if (mlxsw_sp_port->pvid == vid)
		return 0;	/* Dis-allow untagged packets */
	else
		return mlxsw_sp_port->pvid;
}