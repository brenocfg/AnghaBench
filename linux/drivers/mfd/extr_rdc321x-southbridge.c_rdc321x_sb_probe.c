#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct pci_dev* sb_pdev; } ;
struct TYPE_3__ {struct pci_dev* sb_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_enable_device (struct pci_dev*) ; 
 TYPE_2__ rdc321x_gpio_pdata ; 
 int /*<<< orphan*/  rdc321x_sb_cells ; 
 TYPE_1__ rdc321x_wdt_pdata ; 

__attribute__((used)) static int rdc321x_sb_probe(struct pci_dev *pdev,
					const struct pci_device_id *ent)
{
	int err;

	err = pci_enable_device(pdev);
	if (err) {
		dev_err(&pdev->dev, "failed to enable device\n");
		return err;
	}

	rdc321x_gpio_pdata.sb_pdev = pdev;
	rdc321x_wdt_pdata.sb_pdev = pdev;

	return devm_mfd_add_devices(&pdev->dev, -1,
				    rdc321x_sb_cells,
				    ARRAY_SIZE(rdc321x_sb_cells),
				    NULL, 0, NULL);
}