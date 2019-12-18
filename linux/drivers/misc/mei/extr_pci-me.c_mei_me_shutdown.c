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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct mei_device*) ; 
 int /*<<< orphan*/  mei_disable_interrupts (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_unset_pm_domain (struct mei_device*) ; 
 int /*<<< orphan*/  mei_stop (struct mei_device*) ; 
 struct mei_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void mei_me_shutdown(struct pci_dev *pdev)
{
	struct mei_device *dev;

	dev = pci_get_drvdata(pdev);
	if (!dev)
		return;

	dev_dbg(&pdev->dev, "shutdown\n");
	mei_stop(dev);

	mei_me_unset_pm_domain(dev);

	mei_disable_interrupts(dev);
	free_irq(pdev->irq, dev);
}