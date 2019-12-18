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
struct TYPE_2__ {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;
struct mlxsw_sp_port {TYPE_1__ link; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
mlxsw_sp_port_is_pause_en(const struct mlxsw_sp_port *mlxsw_sp_port)
{
	return mlxsw_sp_port->link.tx_pause || mlxsw_sp_port->link.rx_pause;
}