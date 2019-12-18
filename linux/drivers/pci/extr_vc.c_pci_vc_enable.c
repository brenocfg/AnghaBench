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
struct pci_dev {TYPE_1__* bus; } ;
struct TYPE_2__ {struct pci_dev* self; } ;

/* Variables and functions */
 int PCI_CAP_VC_PER_VC_SIZEOF ; 
 scalar_t__ PCI_EXT_CAP_ID (int) ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_VC ; 
 scalar_t__ PCI_EXT_CAP_ID_VC9 ; 
 int PCI_VC_CAP1_EVCC ; 
 int PCI_VC_PORT_CAP1 ; 
 int PCI_VC_RES_CTRL ; 
 int PCI_VC_RES_CTRL_ENABLE ; 
 int PCI_VC_RES_CTRL_ID ; 
 int PCI_VC_RES_STATUS ; 
 int /*<<< orphan*/  PCI_VC_RES_STATUS_NEGO ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 scalar_t__ pci_is_root_bus (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_wait_for_pending (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 int /*<<< orphan*/  pcie_downstream_port (struct pci_dev*) ; 

__attribute__((used)) static void pci_vc_enable(struct pci_dev *dev, int pos, int res)
{
	int ctrl_pos, status_pos, id, pos2, evcc, i, ctrl_pos2, status_pos2;
	u32 ctrl, header, cap1, ctrl2;
	struct pci_dev *link = NULL;

	/* Enable VCs from the downstream device */
	if (!pci_is_pcie(dev) || !pcie_downstream_port(dev))
		return;

	ctrl_pos = pos + PCI_VC_RES_CTRL + (res * PCI_CAP_VC_PER_VC_SIZEOF);
	status_pos = pos + PCI_VC_RES_STATUS + (res * PCI_CAP_VC_PER_VC_SIZEOF);

	pci_read_config_dword(dev, ctrl_pos, &ctrl);
	id = ctrl & PCI_VC_RES_CTRL_ID;

	pci_read_config_dword(dev, pos, &header);

	/* If there is no opposite end of the link, skip to enable */
	if (PCI_EXT_CAP_ID(header) == PCI_EXT_CAP_ID_VC9 ||
	    pci_is_root_bus(dev->bus))
		goto enable;

	pos2 = pci_find_ext_capability(dev->bus->self, PCI_EXT_CAP_ID_VC);
	if (!pos2)
		goto enable;

	pci_read_config_dword(dev->bus->self, pos2 + PCI_VC_PORT_CAP1, &cap1);
	evcc = cap1 & PCI_VC_CAP1_EVCC;

	/* VC0 is hardwired enabled, so we can start with 1 */
	for (i = 1; i < evcc + 1; i++) {
		ctrl_pos2 = pos2 + PCI_VC_RES_CTRL +
				(i * PCI_CAP_VC_PER_VC_SIZEOF);
		status_pos2 = pos2 + PCI_VC_RES_STATUS +
				(i * PCI_CAP_VC_PER_VC_SIZEOF);
		pci_read_config_dword(dev->bus->self, ctrl_pos2, &ctrl2);
		if ((ctrl2 & PCI_VC_RES_CTRL_ID) == id) {
			link = dev->bus->self;
			break;
		}
	}

	if (!link)
		goto enable;

	/* Disable if enabled */
	if (ctrl2 & PCI_VC_RES_CTRL_ENABLE) {
		ctrl2 &= ~PCI_VC_RES_CTRL_ENABLE;
		pci_write_config_dword(link, ctrl_pos2, ctrl2);
	}

	/* Enable on both ends */
	ctrl2 |= PCI_VC_RES_CTRL_ENABLE;
	pci_write_config_dword(link, ctrl_pos2, ctrl2);
enable:
	ctrl |= PCI_VC_RES_CTRL_ENABLE;
	pci_write_config_dword(dev, ctrl_pos, ctrl);

	if (!pci_wait_for_pending(dev, status_pos, PCI_VC_RES_STATUS_NEGO))
		pci_err(dev, "VC%d negotiation stuck pending\n", id);

	if (link && !pci_wait_for_pending(link, status_pos2,
					  PCI_VC_RES_STATUS_NEGO))
		pci_err(link, "VC%d negotiation stuck pending\n", id);
}