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
typedef  int /*<<< orphan*/  u32 ;
struct tango_pcie {scalar_t__ base; } ;
struct pci_config_window {int /*<<< orphan*/  parent; } ;
struct pci_bus {struct pci_config_window* sysdata; } ;

/* Variables and functions */
 scalar_t__ SMP8759_MUX ; 
 struct tango_pcie* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int pci_generic_config_write (struct pci_bus*,unsigned int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int smp8759_config_write(struct pci_bus *bus, unsigned int devfn,
				int where, int size, u32 val)
{
	struct pci_config_window *cfg = bus->sysdata;
	struct tango_pcie *pcie = dev_get_drvdata(cfg->parent);
	int ret;

	writel_relaxed(1, pcie->base + SMP8759_MUX);
	ret = pci_generic_config_write(bus, devfn, where, size, val);
	writel_relaxed(0, pcie->base + SMP8759_MUX);

	return ret;
}