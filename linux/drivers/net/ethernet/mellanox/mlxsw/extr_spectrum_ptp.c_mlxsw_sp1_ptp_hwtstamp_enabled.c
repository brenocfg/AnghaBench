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
struct TYPE_2__ {scalar_t__ egr_types; scalar_t__ ing_types; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;

/* Variables and functions */

__attribute__((used)) static bool mlxsw_sp1_ptp_hwtstamp_enabled(struct mlxsw_sp_port *mlxsw_sp_port)
{
	return mlxsw_sp_port->ptp.ing_types || mlxsw_sp_port->ptp.egr_types;
}