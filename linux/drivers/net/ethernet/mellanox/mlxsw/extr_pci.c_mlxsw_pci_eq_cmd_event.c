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
typedef  int u64 ;
struct TYPE_3__ {int out_param; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int wait_done; int /*<<< orphan*/  wait; TYPE_1__ comp; } ;
struct mlxsw_pci {TYPE_2__ cmd; } ;

/* Variables and functions */
 scalar_t__ mlxsw_pci_eqe_cmd_out_param_h_get (char*) ; 
 int mlxsw_pci_eqe_cmd_out_param_l_get (char*) ; 
 int /*<<< orphan*/  mlxsw_pci_eqe_cmd_status_get (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_pci_eq_cmd_event(struct mlxsw_pci *mlxsw_pci, char *eqe)
{
	mlxsw_pci->cmd.comp.status = mlxsw_pci_eqe_cmd_status_get(eqe);
	mlxsw_pci->cmd.comp.out_param =
		((u64) mlxsw_pci_eqe_cmd_out_param_h_get(eqe)) << 32 |
		mlxsw_pci_eqe_cmd_out_param_l_get(eqe);
	mlxsw_pci->cmd.wait_done = true;
	wake_up(&mlxsw_pci->cmd.wait);
}