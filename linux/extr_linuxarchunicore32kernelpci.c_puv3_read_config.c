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
 int /*<<< orphan*/  CONFIG_CMD (struct pci_bus*,unsigned int,int) ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCICFG_ADDR ; 
 int /*<<< orphan*/  PCICFG_DATA ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
puv3_read_config(struct pci_bus *bus, unsigned int devfn, int where,
			int size, u32 *value)
{
	writel(CONFIG_CMD(bus, devfn, where), PCICFG_ADDR);
	switch (size) {
	case 1:
		*value = (readl(PCICFG_DATA) >> ((where & 3) * 8)) & 0xFF;
		break;
	case 2:
		*value = (readl(PCICFG_DATA) >> ((where & 2) * 8)) & 0xFFFF;
		break;
	case 4:
		*value = readl(PCICFG_DATA);
		break;
	}
	return PCIBIOS_SUCCESSFUL;
}