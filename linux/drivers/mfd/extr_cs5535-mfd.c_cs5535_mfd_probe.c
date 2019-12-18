#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  flags; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 TYPE_1__* cs5535_mfd_cells ; 
 struct resource* cs5535_mfd_resources ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ machine_is_olpc () ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_clone_cell (char*,TYPE_1__*,int) ; 
 TYPE_1__* olpc_acpi_clones ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_resource_end (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static int cs5535_mfd_probe(struct pci_dev *pdev,
		const struct pci_device_id *id)
{
	int err, i;

	err = pci_enable_device(pdev);
	if (err)
		return err;

	/* fill in IO range for each cell; subdrivers handle the region */
	for (i = 0; i < ARRAY_SIZE(cs5535_mfd_cells); i++) {
		int bar = cs5535_mfd_cells[i].id;
		struct resource *r = &cs5535_mfd_resources[bar];

		r->flags = IORESOURCE_IO;
		r->start = pci_resource_start(pdev, bar);
		r->end = pci_resource_end(pdev, bar);

		/* id is used for temporarily storing BAR; unset it now */
		cs5535_mfd_cells[i].id = 0;
	}

	err = mfd_add_devices(&pdev->dev, -1, cs5535_mfd_cells,
			      ARRAY_SIZE(cs5535_mfd_cells), NULL, 0, NULL);
	if (err) {
		dev_err(&pdev->dev, "MFD add devices failed: %d\n", err);
		goto err_disable;
	}

	if (machine_is_olpc())
		mfd_clone_cell("cs5535-acpi", olpc_acpi_clones, ARRAY_SIZE(olpc_acpi_clones));

	dev_info(&pdev->dev, "%zu devices registered.\n",
			ARRAY_SIZE(cs5535_mfd_cells));

	return 0;

err_disable:
	pci_disable_device(pdev);
	return err;
}