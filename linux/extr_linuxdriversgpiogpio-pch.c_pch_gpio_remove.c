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
struct pch_gpio {int /*<<< orphan*/  base; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pch_gpio*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pch_gpio* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void pch_gpio_remove(struct pci_dev *pdev)
{
	struct pch_gpio *chip = pci_get_drvdata(pdev);

	gpiochip_remove(&chip->gpio);
	pci_iounmap(pdev, chip->base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(chip);
}