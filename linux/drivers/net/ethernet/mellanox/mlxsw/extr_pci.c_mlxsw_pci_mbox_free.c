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
struct pci_dev {int dummy; } ;
struct mlxsw_pci_mem_item {int /*<<< orphan*/  mapaddr; int /*<<< orphan*/  buf; } ;
struct mlxsw_pci {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_CMD_MBOX_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_mbox_free(struct mlxsw_pci *mlxsw_pci,
				struct mlxsw_pci_mem_item *mbox)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;

	pci_free_consistent(pdev, MLXSW_CMD_MBOX_SIZE, mbox->buf,
			    mbox->mapaddr);
}