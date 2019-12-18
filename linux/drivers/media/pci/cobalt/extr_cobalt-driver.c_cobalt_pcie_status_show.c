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
typedef  int u16 ;
struct pci_dev {TYPE_1__* bus; } ;
struct cobalt {struct pci_dev* pci_dev; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_DEVCAP ; 
 int PCI_EXP_DEVCAP_PAYLOAD ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_PAYLOAD ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int /*<<< orphan*/  PCI_EXP_DEVSTA ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_MLW ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_NLW ; 
 int /*<<< orphan*/  PCI_EXP_SLTCAP ; 
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int /*<<< orphan*/  cobalt_info (char*,int,...) ; 
 int /*<<< orphan*/  get_link_speed (int) ; 
 int /*<<< orphan*/  get_payload_size (int) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

void cobalt_pcie_status_show(struct cobalt *cobalt)
{
	struct pci_dev *pci_dev = cobalt->pci_dev;
	struct pci_dev *pci_bus_dev = cobalt->pci_dev->bus->self;
	u32 capa;
	u16 stat, ctrl;

	if (!pci_is_pcie(pci_dev) || !pci_is_pcie(pci_bus_dev))
		return;

	/* Device */
	pcie_capability_read_dword(pci_dev, PCI_EXP_DEVCAP, &capa);
	pcie_capability_read_word(pci_dev, PCI_EXP_DEVCTL, &ctrl);
	pcie_capability_read_word(pci_dev, PCI_EXP_DEVSTA, &stat);
	cobalt_info("PCIe device capability 0x%08x: Max payload %d\n",
		    capa, get_payload_size(capa & PCI_EXP_DEVCAP_PAYLOAD));
	cobalt_info("PCIe device control 0x%04x: Max payload %d. Max read request %d\n",
		    ctrl,
		    get_payload_size((ctrl & PCI_EXP_DEVCTL_PAYLOAD) >> 5),
		    get_payload_size((ctrl & PCI_EXP_DEVCTL_READRQ) >> 12));
	cobalt_info("PCIe device status 0x%04x\n", stat);

	/* Link */
	pcie_capability_read_dword(pci_dev, PCI_EXP_LNKCAP, &capa);
	pcie_capability_read_word(pci_dev, PCI_EXP_LNKCTL, &ctrl);
	pcie_capability_read_word(pci_dev, PCI_EXP_LNKSTA, &stat);
	cobalt_info("PCIe link capability 0x%08x: %s per lane and %u lanes\n",
			capa, get_link_speed(capa),
			(capa & PCI_EXP_LNKCAP_MLW) >> 4);
	cobalt_info("PCIe link control 0x%04x\n", ctrl);
	cobalt_info("PCIe link status 0x%04x: %s per lane and %u lanes\n",
		    stat, get_link_speed(stat),
		    (stat & PCI_EXP_LNKSTA_NLW) >> 4);

	/* Bus */
	pcie_capability_read_dword(pci_bus_dev, PCI_EXP_LNKCAP, &capa);
	cobalt_info("PCIe bus link capability 0x%08x: %s per lane and %u lanes\n",
			capa, get_link_speed(capa),
			(capa & PCI_EXP_LNKCAP_MLW) >> 4);

	/* Slot */
	pcie_capability_read_dword(pci_dev, PCI_EXP_SLTCAP, &capa);
	pcie_capability_read_word(pci_dev, PCI_EXP_SLTCTL, &ctrl);
	pcie_capability_read_word(pci_dev, PCI_EXP_SLTSTA, &stat);
	cobalt_info("PCIe slot capability 0x%08x\n", capa);
	cobalt_info("PCIe slot control 0x%04x\n", ctrl);
	cobalt_info("PCIe slot status 0x%04x\n", stat);
}