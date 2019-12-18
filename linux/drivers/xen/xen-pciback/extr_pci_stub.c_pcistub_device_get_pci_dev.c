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
struct xen_pcibk_device {int dummy; } ;
struct pcistub_device {int /*<<< orphan*/  lock; struct pci_dev* dev; struct xen_pcibk_device* pdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcistub_device_get (struct pcistub_device*) ; 
 int /*<<< orphan*/  pcistub_device_put (struct pcistub_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct pci_dev *pcistub_device_get_pci_dev(struct xen_pcibk_device *pdev,
						  struct pcistub_device *psdev)
{
	struct pci_dev *pci_dev = NULL;
	unsigned long flags;

	pcistub_device_get(psdev);

	spin_lock_irqsave(&psdev->lock, flags);
	if (!psdev->pdev) {
		psdev->pdev = pdev;
		pci_dev = psdev->dev;
	}
	spin_unlock_irqrestore(&psdev->lock, flags);

	if (!pci_dev)
		pcistub_device_put(psdev);

	return pci_dev;
}