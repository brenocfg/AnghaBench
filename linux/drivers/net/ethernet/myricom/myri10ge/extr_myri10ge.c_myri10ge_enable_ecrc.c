#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {TYPE_3__* bus; } ;
struct myri10ge_priv {TYPE_2__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct pci_dev* self; } ;
struct TYPE_5__ {struct device dev; TYPE_1__* bus; } ;
struct TYPE_4__ {struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_CAP ; 
 unsigned int PCI_ERR_CAP_ECRC_GENC ; 
 unsigned int PCI_ERR_CAP_ECRC_GENE ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int myri10ge_ecrc_enable ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 int pci_read_config_dword (struct pci_dev*,scalar_t__,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void myri10ge_enable_ecrc(struct myri10ge_priv *mgp)
{
	struct pci_dev *bridge = mgp->pdev->bus->self;
	struct device *dev = &mgp->pdev->dev;
	int cap;
	unsigned err_cap;
	int ret;

	if (!myri10ge_ecrc_enable || !bridge)
		return;

	/* check that the bridge is a root port */
	if (pci_pcie_type(bridge) != PCI_EXP_TYPE_ROOT_PORT) {
		if (myri10ge_ecrc_enable > 1) {
			struct pci_dev *prev_bridge, *old_bridge = bridge;

			/* Walk the hierarchy up to the root port
			 * where ECRC has to be enabled */
			do {
				prev_bridge = bridge;
				bridge = bridge->bus->self;
				if (!bridge || prev_bridge == bridge) {
					dev_err(dev,
						"Failed to find root port"
						" to force ECRC\n");
					return;
				}
			} while (pci_pcie_type(bridge) !=
				 PCI_EXP_TYPE_ROOT_PORT);

			dev_info(dev,
				 "Forcing ECRC on non-root port %s"
				 " (enabling on root port %s)\n",
				 pci_name(old_bridge), pci_name(bridge));
		} else {
			dev_err(dev,
				"Not enabling ECRC on non-root port %s\n",
				pci_name(bridge));
			return;
		}
	}

	cap = pci_find_ext_capability(bridge, PCI_EXT_CAP_ID_ERR);
	if (!cap)
		return;

	ret = pci_read_config_dword(bridge, cap + PCI_ERR_CAP, &err_cap);
	if (ret) {
		dev_err(dev, "failed reading ext-conf-space of %s\n",
			pci_name(bridge));
		dev_err(dev, "\t pci=nommconf in use? "
			"or buggy/incomplete/absent ACPI MCFG attr?\n");
		return;
	}
	if (!(err_cap & PCI_ERR_CAP_ECRC_GENC))
		return;

	err_cap |= PCI_ERR_CAP_ECRC_GENE;
	pci_write_config_dword(bridge, cap + PCI_ERR_CAP, err_cap);
	dev_info(dev, "Enabled ECRC on upstream bridge %s\n", pci_name(bridge));
}