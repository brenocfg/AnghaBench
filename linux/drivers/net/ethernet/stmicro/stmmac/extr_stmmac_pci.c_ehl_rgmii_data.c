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
struct plat_stmmacenet_data {int bus_id; int /*<<< orphan*/  interface; scalar_t__ phy_addr; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII ; 
 int ehl_common_data (struct pci_dev*,struct plat_stmmacenet_data*) ; 

__attribute__((used)) static int ehl_rgmii_data(struct pci_dev *pdev,
			  struct plat_stmmacenet_data *plat)
{
	plat->bus_id = 1;
	plat->phy_addr = 0;
	plat->interface = PHY_INTERFACE_MODE_RGMII;
	return ehl_common_data(pdev, plat);
}