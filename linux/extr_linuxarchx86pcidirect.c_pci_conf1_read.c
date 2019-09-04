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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_CONF1_ADDRESS (unsigned int,unsigned int,int) ; 
 int inb (int) ; 
 int inl (int) ; 
 int inw (int) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_config_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pci_conf1_read(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int reg, int len, u32 *value)
{
	unsigned long flags;

	if (seg || (bus > 255) || (devfn > 255) || (reg > 4095)) {
		*value = -1;
		return -EINVAL;
	}

	raw_spin_lock_irqsave(&pci_config_lock, flags);

	outl(PCI_CONF1_ADDRESS(bus, devfn, reg), 0xCF8);

	switch (len) {
	case 1:
		*value = inb(0xCFC + (reg & 3));
		break;
	case 2:
		*value = inw(0xCFC + (reg & 2));
		break;
	case 4:
		*value = inl(0xCFC);
		break;
	}

	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	return 0;
}