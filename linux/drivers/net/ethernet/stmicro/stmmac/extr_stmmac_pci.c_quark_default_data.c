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
struct plat_stmmacenet_data {int phy_addr; TYPE_1__* dma_cfg; int /*<<< orphan*/  interface; int /*<<< orphan*/  bus_id; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int pbl; int pblx8; int fixed_burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMI_BOARD_NAME ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  common_default_data (struct plat_stmmacenet_data*) ; 
 scalar_t__ dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_id (struct pci_dev*) ; 
 int /*<<< orphan*/  quark_pci_dmi ; 
 int stmmac_pci_find_phy_addr (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int quark_default_data(struct pci_dev *pdev,
			      struct plat_stmmacenet_data *plat)
{
	int ret;

	/* Set common default data first */
	common_default_data(plat);

	/*
	 * Refuse to load the driver and register net device if MAC controller
	 * does not connect to any PHY interface.
	 */
	ret = stmmac_pci_find_phy_addr(pdev, quark_pci_dmi);
	if (ret < 0) {
		/* Return error to the caller on DMI enabled boards. */
		if (dmi_get_system_info(DMI_BOARD_NAME))
			return ret;

		/*
		 * Galileo boards with old firmware don't support DMI. We always
		 * use 1 here as PHY address, so at least the first found MAC
		 * controller would be probed.
		 */
		ret = 1;
	}

	plat->bus_id = pci_dev_id(pdev);
	plat->phy_addr = ret;
	plat->interface = PHY_INTERFACE_MODE_RMII;

	plat->dma_cfg->pbl = 16;
	plat->dma_cfg->pblx8 = true;
	plat->dma_cfg->fixed_burst = 1;
	/* AXI (TODO) */

	return 0;
}