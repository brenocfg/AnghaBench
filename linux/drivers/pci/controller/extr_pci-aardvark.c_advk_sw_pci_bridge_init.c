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
struct TYPE_2__ {int vendor; int device; int class_revision; int /*<<< orphan*/  intpin; void* pref_mem_limit; void* pref_mem_base; void* iolimit; void* iobase; } ;
struct pci_bridge_emul {int has_pcie; int /*<<< orphan*/ * ops; struct advk_pcie* data; TYPE_1__ conf; } ;
struct advk_pcie {struct pci_bridge_emul bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_CORE_DEV_ID_REG ; 
 int /*<<< orphan*/  PCIE_CORE_DEV_REV_REG ; 
 int /*<<< orphan*/  PCIE_CORE_INT_A_ASSERT_ENABLE ; 
 void* PCI_IO_RANGE_TYPE_32 ; 
 void* PCI_PREF_RANGE_TYPE_64 ; 
 int /*<<< orphan*/  advk_pci_bridge_emul_ops ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bridge_emul_init (struct pci_bridge_emul*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void advk_sw_pci_bridge_init(struct advk_pcie *pcie)
{
	struct pci_bridge_emul *bridge = &pcie->bridge;

	bridge->conf.vendor = advk_readl(pcie, PCIE_CORE_DEV_ID_REG) & 0xffff;
	bridge->conf.device = advk_readl(pcie, PCIE_CORE_DEV_ID_REG) >> 16;
	bridge->conf.class_revision =
		advk_readl(pcie, PCIE_CORE_DEV_REV_REG) & 0xff;

	/* Support 32 bits I/O addressing */
	bridge->conf.iobase = PCI_IO_RANGE_TYPE_32;
	bridge->conf.iolimit = PCI_IO_RANGE_TYPE_32;

	/* Support 64 bits memory pref */
	bridge->conf.pref_mem_base = PCI_PREF_RANGE_TYPE_64;
	bridge->conf.pref_mem_limit = PCI_PREF_RANGE_TYPE_64;

	/* Support interrupt A for MSI feature */
	bridge->conf.intpin = PCIE_CORE_INT_A_ASSERT_ENABLE;

	bridge->has_pcie = true;
	bridge->data = pcie;
	bridge->ops = &advk_pci_bridge_emul_ops;

	pci_bridge_emul_init(bridge, 0);

}