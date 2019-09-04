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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP13XX_XBG_BECSR ; 
 int PCIBIOS_SUCCESSFUL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 unsigned long iop13xx_atux_cfg_address (struct pci_bus*,unsigned int,int) ; 
 scalar_t__ iop13xx_atux_pci_status (int) ; 
 int iop13xx_atux_read (unsigned long) ; 
 scalar_t__ is_atux_occdr_error () ; 

__attribute__((used)) static int
iop13xx_atux_read_config(struct pci_bus *bus, unsigned int devfn, int where,
		int size, u32 *value)
{
	unsigned long addr = iop13xx_atux_cfg_address(bus, devfn, where);
	u32 val = iop13xx_atux_read(addr) >> ((where & 3) * 8);

	if (iop13xx_atux_pci_status(1) || is_atux_occdr_error()) {
		__raw_writel(__raw_readl(IOP13XX_XBG_BECSR) & 3,
			IOP13XX_XBG_BECSR);
		val = 0xffffffff;
	}

	*value = val;

	return PCIBIOS_SUCCESSFUL;
}