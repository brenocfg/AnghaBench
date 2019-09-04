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
typedef  int u16 ;
struct mlxsw_pci_mem_item {int /*<<< orphan*/  mapaddr; int /*<<< orphan*/  buf; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int count; struct mlxsw_pci_mem_item* items; } ;
struct mlxsw_pci {TYPE_1__ fw_area; int /*<<< orphan*/  pdev; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXSW_CMD_MAP_FA_VPM_ENTRIES_MAX ; 
 int /*<<< orphan*/  MLXSW_PCI_PAGE_SIZE ; 
 struct mlxsw_pci_mem_item* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_pci_mem_item*) ; 
 int mlxsw_cmd_map_fa (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_map_fa_log2size_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_map_fa_pa_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_zero (char*) ; 
 int /*<<< orphan*/  pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_pci_fw_area_init(struct mlxsw_pci *mlxsw_pci, char *mbox,
				  u16 num_pages)
{
	struct mlxsw_pci_mem_item *mem_item;
	int nent = 0;
	int i;
	int err;

	mlxsw_pci->fw_area.items = kcalloc(num_pages, sizeof(*mem_item),
					   GFP_KERNEL);
	if (!mlxsw_pci->fw_area.items)
		return -ENOMEM;
	mlxsw_pci->fw_area.count = num_pages;

	mlxsw_cmd_mbox_zero(mbox);
	for (i = 0; i < num_pages; i++) {
		mem_item = &mlxsw_pci->fw_area.items[i];

		mem_item->size = MLXSW_PCI_PAGE_SIZE;
		mem_item->buf = pci_alloc_consistent(mlxsw_pci->pdev,
						     mem_item->size,
						     &mem_item->mapaddr);
		if (!mem_item->buf) {
			err = -ENOMEM;
			goto err_alloc;
		}
		mlxsw_cmd_mbox_map_fa_pa_set(mbox, nent, mem_item->mapaddr);
		mlxsw_cmd_mbox_map_fa_log2size_set(mbox, nent, 0); /* 1 page */
		if (++nent == MLXSW_CMD_MAP_FA_VPM_ENTRIES_MAX) {
			err = mlxsw_cmd_map_fa(mlxsw_pci->core, mbox, nent);
			if (err)
				goto err_cmd_map_fa;
			nent = 0;
			mlxsw_cmd_mbox_zero(mbox);
		}
	}

	if (nent) {
		err = mlxsw_cmd_map_fa(mlxsw_pci->core, mbox, nent);
		if (err)
			goto err_cmd_map_fa;
	}

	return 0;

err_cmd_map_fa:
err_alloc:
	for (i--; i >= 0; i--) {
		mem_item = &mlxsw_pci->fw_area.items[i];

		pci_free_consistent(mlxsw_pci->pdev, mem_item->size,
				    mem_item->buf, mem_item->mapaddr);
	}
	kfree(mlxsw_pci->fw_area.items);
	return err;
}