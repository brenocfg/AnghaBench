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
struct TYPE_2__ {int nopoll; } ;
struct mlxsw_pci {TYPE_1__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_pci_cq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_eq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_queue_group_fini (struct mlxsw_pci*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_pci_rdq_ops ; 
 int /*<<< orphan*/  mlxsw_pci_sdq_ops ; 

__attribute__((used)) static void mlxsw_pci_aqs_fini(struct mlxsw_pci *mlxsw_pci)
{
	mlxsw_pci->cmd.nopoll = false;
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_rdq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_sdq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_cq_ops);
	mlxsw_pci_queue_group_fini(mlxsw_pci, &mlxsw_pci_eq_ops);
}