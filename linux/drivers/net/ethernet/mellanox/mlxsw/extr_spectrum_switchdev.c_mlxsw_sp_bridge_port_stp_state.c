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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  stp_state; } ;

/* Variables and functions */

u8
mlxsw_sp_bridge_port_stp_state(struct mlxsw_sp_bridge_port *bridge_port)
{
	return bridge_port->stp_state;
}