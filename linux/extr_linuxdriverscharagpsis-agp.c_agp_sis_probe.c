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
typedef  scalar_t__ u8 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  dev; } ;
struct agp_bridge_data {int /*<<< orphan*/  mode; scalar_t__ capndx; struct pci_dev* dev; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ PCI_AGP_STATUS ; 
 int /*<<< orphan*/  PCI_CAP_ID_AGP ; 
 int agp_add_bridge (struct agp_bridge_data*) ; 
 struct agp_bridge_data* agp_alloc_bridge () ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_agp_version (struct agp_bridge_data*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct agp_bridge_data*) ; 
 int /*<<< orphan*/  sis_driver ; 
 int /*<<< orphan*/  sis_get_driver (struct agp_bridge_data*) ; 

__attribute__((used)) static int agp_sis_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	struct agp_bridge_data *bridge;
	u8 cap_ptr;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	if (!cap_ptr)
		return -ENODEV;


	dev_info(&pdev->dev, "SiS chipset [%04x/%04x]\n",
		 pdev->vendor, pdev->device);
	bridge = agp_alloc_bridge();
	if (!bridge)
		return -ENOMEM;

	bridge->driver = &sis_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	get_agp_version(bridge);

	/* Fill in the mode register */
	pci_read_config_dword(pdev, bridge->capndx+PCI_AGP_STATUS, &bridge->mode);
	sis_get_driver(bridge);

	pci_set_drvdata(pdev, bridge);
	return agp_add_bridge(bridge);
}