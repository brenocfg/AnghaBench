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
struct mlxsw_pci_mem_item {int /*<<< orphan*/  mapaddr; int /*<<< orphan*/  buf; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int count; struct mlxsw_pci_mem_item* items; } ;
struct mlxsw_pci {TYPE_1__ fw_area; int /*<<< orphan*/  pdev; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_pci_mem_item*) ; 
 int /*<<< orphan*/  mlxsw_cmd_unmap_fa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_pci_fw_area_fini(struct mlxsw_pci *mlxsw_pci)
{
	struct mlxsw_pci_mem_item *mem_item;
	int i;

	mlxsw_cmd_unmap_fa(mlxsw_pci->core);

	for (i = 0; i < mlxsw_pci->fw_area.count; i++) {
		mem_item = &mlxsw_pci->fw_area.items[i];

		pci_free_consistent(mlxsw_pci->pdev, mem_item->size,
				    mem_item->buf, mem_item->mapaddr);
	}
	kfree(mlxsw_pci->fw_area.items);
}