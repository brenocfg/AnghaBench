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
struct TYPE_2__ {int device; int class_revision; void* iolimit; void* iobase; int /*<<< orphan*/  vendor; } ;
struct pci_bridge_emul {int has_pcie; int /*<<< orphan*/ * ops; struct mvebu_pcie_port* data; TYPE_1__ conf; } ;
struct mvebu_pcie_port {struct pci_bridge_emul bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_DEV_ID_OFF ; 
 int /*<<< orphan*/  PCIE_DEV_REV_OFF ; 
 int /*<<< orphan*/  PCI_BRIDGE_EMUL_NO_PREFETCHABLE_BAR ; 
 void* PCI_IO_RANGE_TYPE_32 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_MARVELL ; 
 scalar_t__ mvebu_has_ioport (struct mvebu_pcie_port*) ; 
 int /*<<< orphan*/  mvebu_pci_bridge_emul_ops ; 
 int mvebu_readl (struct mvebu_pcie_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bridge_emul_init (struct pci_bridge_emul*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_pci_bridge_emul_init(struct mvebu_pcie_port *port)
{
	struct pci_bridge_emul *bridge = &port->bridge;

	bridge->conf.vendor = PCI_VENDOR_ID_MARVELL;
	bridge->conf.device = mvebu_readl(port, PCIE_DEV_ID_OFF) >> 16;
	bridge->conf.class_revision =
		mvebu_readl(port, PCIE_DEV_REV_OFF) & 0xff;

	if (mvebu_has_ioport(port)) {
		/* We support 32 bits I/O addressing */
		bridge->conf.iobase = PCI_IO_RANGE_TYPE_32;
		bridge->conf.iolimit = PCI_IO_RANGE_TYPE_32;
	}

	bridge->has_pcie = true;
	bridge->data = port;
	bridge->ops = &mvebu_pci_bridge_emul_ops;

	pci_bridge_emul_init(bridge, PCI_BRIDGE_EMUL_NO_PREFETCHABLE_BAR);
}