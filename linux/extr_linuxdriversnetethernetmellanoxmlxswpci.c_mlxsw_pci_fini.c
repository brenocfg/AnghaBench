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
struct TYPE_2__ {int /*<<< orphan*/  in_mbox; int /*<<< orphan*/  out_mbox; } ;
struct mlxsw_pci {TYPE_1__ cmd; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_aqs_fini (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_free_irq_vectors (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_fw_area_fini (struct mlxsw_pci*) ; 
 int /*<<< orphan*/  mlxsw_pci_mbox_free (struct mlxsw_pci*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_fini(void *bus_priv)
{
	struct mlxsw_pci *mlxsw_pci = bus_priv;

	free_irq(pci_irq_vector(mlxsw_pci->pdev, 0), mlxsw_pci);
	mlxsw_pci_aqs_fini(mlxsw_pci);
	mlxsw_pci_fw_area_fini(mlxsw_pci);
	mlxsw_pci_free_irq_vectors(mlxsw_pci);
	mlxsw_pci_mbox_free(mlxsw_pci, &mlxsw_pci->cmd.out_mbox);
	mlxsw_pci_mbox_free(mlxsw_pci, &mlxsw_pci->cmd.in_mbox);
}