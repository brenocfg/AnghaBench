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
struct hwtstamp_config {int dummy; } ;
struct TYPE_2__ {struct hwtstamp_config hwtstamp_config; } ;
struct mlxsw_sp_port {TYPE_1__ ptp; } ;

/* Variables and functions */

int mlxsw_sp1_ptp_hwtstamp_get(struct mlxsw_sp_port *mlxsw_sp_port,
			       struct hwtstamp_config *config)
{
	*config = mlxsw_sp_port->ptp.hwtstamp_config;
	return 0;
}