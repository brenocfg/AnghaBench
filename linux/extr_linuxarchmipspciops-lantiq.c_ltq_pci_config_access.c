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
struct pci_bus {unsigned int number; } ;

/* Variables and functions */
 unsigned int LTQ_PCI_CFG_BUSNUM_SHF ; 
 unsigned int LTQ_PCI_CFG_FUNNUM_SHF ; 
 unsigned char PCI_ACCESS_READ ; 
 unsigned char PCI_ACCESS_WRITE ; 
 int /*<<< orphan*/  ebu_lock ; 
 scalar_t__ ltq_pci_mapped_cfg ; 
 int ltq_r32 (int*) ; 
 int /*<<< orphan*/  ltq_w32 (int,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int swab32 (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ltq_pci_config_access(unsigned char access_type, struct pci_bus *bus,
	unsigned int devfn, unsigned int where, u32 *data)
{
	unsigned long cfg_base;
	unsigned long flags;
	u32 temp;

	/* we support slot from 0 to 15 dev_fn & 0x68 (AD29) is the
	   SoC itself */
	if ((bus->number != 0) || ((devfn & 0xf8) > 0x78)
		|| ((devfn & 0xf8) == 0) || ((devfn & 0xf8) == 0x68))
		return 1;

	spin_lock_irqsave(&ebu_lock, flags);

	cfg_base = (unsigned long) ltq_pci_mapped_cfg;
	cfg_base |= (bus->number << LTQ_PCI_CFG_BUSNUM_SHF) | (devfn <<
			LTQ_PCI_CFG_FUNNUM_SHF) | (where & ~0x3);

	/* Perform access */
	if (access_type == PCI_ACCESS_WRITE) {
		ltq_w32(swab32(*data), ((u32 *)cfg_base));
	} else {
		*data = ltq_r32(((u32 *)(cfg_base)));
		*data = swab32(*data);
	}
	wmb();

	/* clean possible Master abort */
	cfg_base = (unsigned long) ltq_pci_mapped_cfg;
	cfg_base |= (0x0 << LTQ_PCI_CFG_FUNNUM_SHF) + 4;
	temp = ltq_r32(((u32 *)(cfg_base)));
	temp = swab32(temp);
	cfg_base = (unsigned long) ltq_pci_mapped_cfg;
	cfg_base |= (0x68 << LTQ_PCI_CFG_FUNNUM_SHF) + 4;
	ltq_w32(temp, ((u32 *)cfg_base));

	spin_unlock_irqrestore(&ebu_lock, flags);

	if (((*data) == 0xffffffff) && (access_type == PCI_ACCESS_READ))
		return 1;

	return 0;
}