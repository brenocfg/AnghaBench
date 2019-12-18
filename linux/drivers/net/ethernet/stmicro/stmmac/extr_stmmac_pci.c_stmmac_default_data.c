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
struct plat_stmmacenet_data {int bus_id; TYPE_1__* dma_cfg; int /*<<< orphan*/  interface; scalar_t__ phy_addr; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int pbl; int pblx8; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  common_default_data (struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int stmmac_default_data(struct pci_dev *pdev,
			       struct plat_stmmacenet_data *plat)
{
	/* Set common default data first */
	common_default_data(plat);

	plat->bus_id = 1;
	plat->phy_addr = 0;
	plat->interface = PHY_INTERFACE_MODE_GMII;

	plat->dma_cfg->pbl = 32;
	plat->dma_cfg->pblx8 = true;
	/* TODO: AXI */

	return 0;
}