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
struct r852_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  card_detect_work; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct r852_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  r852_disable_irqs (struct r852_device*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r852_shutdown(struct pci_dev *pci_dev)
{
	struct r852_device *dev = pci_get_drvdata(pci_dev);

	cancel_delayed_work_sync(&dev->card_detect_work);
	r852_disable_irqs(dev);
	synchronize_irq(dev->irq);
	pci_disable_device(pci_dev);
}