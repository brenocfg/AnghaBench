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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool acpi_pci_irq_valid(struct pci_dev *dev, u8 pin)
{
#ifdef CONFIG_X86
	/*
	 * On x86 irq line 0xff means "unknown" or "no connection"
	 * (PCI 3.0, Section 6.2.4, footnote on page 223).
	 */
	if (dev->irq == 0xff) {
		dev->irq = IRQ_NOTCONNECTED;
		dev_warn(&dev->dev, "PCI INT %c: not connected\n",
			 pin_name(pin));
		return false;
	}
#endif
	return true;
}