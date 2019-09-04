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
struct pci_channel {int dummy; } ;
struct pci_bus {struct pci_channel* sysdata; } ;

/* Variables and functions */
 int CONFIG_CMD (struct pci_bus*,unsigned int,int) ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  SH4_PCIPAR ; 
 int /*<<< orphan*/  SH4_PCIPDR ; 
 int /*<<< orphan*/  pci_config_lock ; 
 int pci_read_reg (struct pci_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_reg (struct pci_channel*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sh4_pci_write(struct pci_bus *bus, unsigned int devfn,
			 int where, int size, u32 val)
{
	struct pci_channel *chan = bus->sysdata;
	unsigned long flags;
	int shift;
	u32 data;

	raw_spin_lock_irqsave(&pci_config_lock, flags);
	pci_write_reg(chan, CONFIG_CMD(bus, devfn, where), SH4_PCIPAR);
	data = pci_read_reg(chan, SH4_PCIPDR);
	raw_spin_unlock_irqrestore(&pci_config_lock, flags);

	switch (size) {
	case 1:
		shift = (where & 3) << 3;
		data &= ~(0xff << shift);
		data |= ((val & 0xff) << shift);
		break;
	case 2:
		shift = (where & 2) << 3;
		data &= ~(0xffff << shift);
		data |= ((val & 0xffff) << shift);
		break;
	case 4:
		data = val;
		break;
	default:
		return PCIBIOS_FUNC_NOT_SUPPORTED;
	}

	pci_write_reg(chan, data, SH4_PCIPDR);

	return PCIBIOS_SUCCESSFUL;
}