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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_core {int /*<<< orphan*/  bus_priv; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_frc_l ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

u32 mlxsw_core_read_frc_l(struct mlxsw_core *mlxsw_core)
{
	return mlxsw_core->bus->read_frc_l(mlxsw_core->bus_priv);
}