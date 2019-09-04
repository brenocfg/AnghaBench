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
struct sta2x11_mapping {scalar_t__ amba_base; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHB_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHB_CRW (int) ; 
 int AHB_CRW_ENABLE ; 
 int AHB_CRW_WTYPE_MEM ; 
 int /*<<< orphan*/  AHB_PEXHBASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHB_PEXLBASE (int /*<<< orphan*/ ) ; 
 int STA2X11_AMBA_SIZE ; 
 int STA2X11_NR_FUNCS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sta2x11_pdev_to_ep (struct pci_dev*) ; 
 struct sta2x11_mapping* sta2x11_pdev_to_mapping (struct pci_dev*) ; 

__attribute__((used)) static void sta2x11_map_ep(struct pci_dev *pdev)
{
	struct sta2x11_mapping *map = sta2x11_pdev_to_mapping(pdev);
	int i;

	if (!map)
		return;
	pci_read_config_dword(pdev, AHB_BASE(0), &map->amba_base);

	/* Configure AHB mapping */
	pci_write_config_dword(pdev, AHB_PEXLBASE(0), 0);
	pci_write_config_dword(pdev, AHB_PEXHBASE(0), 0);
	pci_write_config_dword(pdev, AHB_CRW(0), STA2X11_AMBA_SIZE |
			       AHB_CRW_WTYPE_MEM | AHB_CRW_ENABLE);

	/* Disable all the other windows */
	for (i = 1; i < STA2X11_NR_FUNCS; i++)
		pci_write_config_dword(pdev, AHB_CRW(i), 0);

	dev_info(&pdev->dev,
		 "sta2x11: Map EP %i: AMBA address %#8x-%#8x\n",
		 sta2x11_pdev_to_ep(pdev),  map->amba_base,
		 map->amba_base + STA2X11_AMBA_SIZE - 1);
}