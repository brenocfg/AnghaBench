#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_controller {int /*<<< orphan*/  cfg_addr; int /*<<< orphan*/  cfg_data; } ;
struct pci_bus {int number; } ;
struct TYPE_2__ {scalar_t__ (* pci_exclude_device ) (struct pci_controller*,int,unsigned int) ;} ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int in_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 TYPE_1__ ppc_md ; 
 scalar_t__ stub1 (struct pci_controller*,int,unsigned int) ; 

__attribute__((used)) static int
mpc52xx_pci_read_config(struct pci_bus *bus, unsigned int devfn,
				int offset, int len, u32 *val)
{
	struct pci_controller *hose = pci_bus_to_host(bus);
	u32 value;

	if (ppc_md.pci_exclude_device)
		if (ppc_md.pci_exclude_device(hose, bus->number, devfn))
			return PCIBIOS_DEVICE_NOT_FOUND;

	out_be32(hose->cfg_addr,
		(1 << 31) |
		(bus->number << 16) |
		(devfn << 8) |
		(offset & 0xfc));
	mb();

#if defined(CONFIG_PPC_MPC5200_BUGFIX)
	if (bus->number) {
		/* workaround for the bug 435 of the MPC5200 (L25R);
		 * Don't do 32 bits config access during type-1 cycles */
		switch (len) {
		      case 1:
			value = in_8(((u8 __iomem *)hose->cfg_data) +
			             (offset & 3));
			break;
		      case 2:
			value = in_le16(((u16 __iomem *)hose->cfg_data) +
			                ((offset>>1) & 1));
			break;

		      default:
			value = in_le16((u16 __iomem *)hose->cfg_data) |
				(in_le16(((u16 __iomem *)hose->cfg_data) + 1) << 16);
			break;
		}
	}
	else
#endif
	{
		value = in_le32(hose->cfg_data);

		if (len != 4) {
			value >>= ((offset & 0x3) << 3);
			value &= 0xffffffff >> (32 - (len << 3));
		}
	}

	*val = value;

	out_be32(hose->cfg_addr, 0);
	mb();

	return PCIBIOS_SUCCESSFUL;
}