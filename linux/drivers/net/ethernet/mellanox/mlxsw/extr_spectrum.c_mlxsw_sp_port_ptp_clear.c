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
struct mlxsw_sp_port {TYPE_2__* mlxsw_sp; } ;
struct hwtstamp_config {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {TYPE_1__* ptp_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hwtstamp_set ) (struct mlxsw_sp_port*,struct hwtstamp_config*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_port*,struct hwtstamp_config*) ; 

__attribute__((used)) static inline void mlxsw_sp_port_ptp_clear(struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct hwtstamp_config config = {0};

	mlxsw_sp_port->mlxsw_sp->ptp_ops->hwtstamp_set(mlxsw_sp_port, &config);
}