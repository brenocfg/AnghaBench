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
struct pci_dev {scalar_t__ irq; scalar_t__ irq_managed; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_should_keep_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_unmap_irq (scalar_t__) ; 

__attribute__((used)) static void intel_mid_pci_irq_disable(struct pci_dev *dev)
{
	if (!mp_should_keep_irq(&dev->dev) && dev->irq_managed &&
	    dev->irq > 0) {
		mp_unmap_irq(dev->irq);
		dev->irq_managed = 0;
	}
}