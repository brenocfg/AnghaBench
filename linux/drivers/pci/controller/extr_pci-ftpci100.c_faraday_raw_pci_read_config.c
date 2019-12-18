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
struct faraday_pci {scalar_t__ base; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCI_CONFIG ; 
 int PCI_CONF_BUS (int) ; 
 int PCI_CONF_DEVICE (int /*<<< orphan*/ ) ; 
 int PCI_CONF_ENABLE ; 
 int PCI_CONF_FUNCTION (int /*<<< orphan*/ ) ; 
 int PCI_CONF_WHERE (int) ; 
 scalar_t__ PCI_DATA ; 
 int /*<<< orphan*/  PCI_FUNC (unsigned int) ; 
 int /*<<< orphan*/  PCI_SLOT (unsigned int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int faraday_raw_pci_read_config(struct faraday_pci *p, int bus_number,
				       unsigned int fn, int config, int size,
				       u32 *value)
{
	writel(PCI_CONF_BUS(bus_number) |
			PCI_CONF_DEVICE(PCI_SLOT(fn)) |
			PCI_CONF_FUNCTION(PCI_FUNC(fn)) |
			PCI_CONF_WHERE(config) |
			PCI_CONF_ENABLE,
			p->base + PCI_CONFIG);

	*value = readl(p->base + PCI_DATA);

	if (size == 1)
		*value = (*value >> (8 * (config & 3))) & 0xFF;
	else if (size == 2)
		*value = (*value >> (8 * (config & 3))) & 0xFFFF;

	return PCIBIOS_SUCCESSFUL;
}