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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ngene {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ngene_unlink (struct ngene*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct ngene* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  shutdown_workaround ; 

void ngene_shutdown(struct pci_dev *pdev)
{
	struct ngene *dev = pci_get_drvdata(pdev);

	if (!dev || !shutdown_workaround)
		return;

	dev_info(&pdev->dev, "shutdown workaround...\n");
	ngene_unlink(dev);
	pci_disable_device(pdev);
}