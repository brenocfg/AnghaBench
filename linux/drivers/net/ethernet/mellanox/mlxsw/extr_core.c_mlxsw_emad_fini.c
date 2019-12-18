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
struct TYPE_4__ {int use_emad; } ;
struct mlxsw_core {int /*<<< orphan*/  emad_wq; TYPE_2__ emad; TYPE_1__* bus; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int MLXSW_BUS_F_TXRX ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_trap_unregister (struct mlxsw_core*,int /*<<< orphan*/ *,struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_emad_rx_listener ; 

__attribute__((used)) static void mlxsw_emad_fini(struct mlxsw_core *mlxsw_core)
{

	if (!(mlxsw_core->bus->features & MLXSW_BUS_F_TXRX))
		return;

	mlxsw_core->emad.use_emad = false;
	mlxsw_core_trap_unregister(mlxsw_core, &mlxsw_emad_rx_listener,
				   mlxsw_core);
	destroy_workqueue(mlxsw_core->emad_wq);
}