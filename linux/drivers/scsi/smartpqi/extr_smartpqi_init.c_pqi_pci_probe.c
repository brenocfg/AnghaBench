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
struct pqi_ctrl_info {struct pci_dev* pci_dev; } ;
struct pci_device_id {scalar_t__ subvendor; scalar_t__ subdevice; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int NUMA_NO_NODE ; 
 scalar_t__ PCI_ANY_ID ; 
 int cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct pqi_ctrl_info* pqi_alloc_ctrl_info (int) ; 
 int pqi_ctrl_init (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_disable_device_id_wildcards ; 
 int pqi_pci_init (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  pqi_print_ctrl_info (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  pqi_remove_ctrl (struct pqi_ctrl_info*) ; 
 int /*<<< orphan*/  set_dev_node (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pqi_pci_probe(struct pci_dev *pci_dev,
	const struct pci_device_id *id)
{
	int rc;
	int node, cp_node;
	struct pqi_ctrl_info *ctrl_info;

	pqi_print_ctrl_info(pci_dev, id);

	if (pqi_disable_device_id_wildcards &&
		id->subvendor == PCI_ANY_ID &&
		id->subdevice == PCI_ANY_ID) {
		dev_warn(&pci_dev->dev,
			"controller not probed because device ID wildcards are disabled\n");
		return -ENODEV;
	}

	if (id->subvendor == PCI_ANY_ID || id->subdevice == PCI_ANY_ID)
		dev_warn(&pci_dev->dev,
			"controller device ID matched using wildcards\n");

	node = dev_to_node(&pci_dev->dev);
	if (node == NUMA_NO_NODE) {
		cp_node = cpu_to_node(0);
		if (cp_node == NUMA_NO_NODE)
			cp_node = 0;
		set_dev_node(&pci_dev->dev, cp_node);
	}

	ctrl_info = pqi_alloc_ctrl_info(node);
	if (!ctrl_info) {
		dev_err(&pci_dev->dev,
			"failed to allocate controller info block\n");
		return -ENOMEM;
	}

	ctrl_info->pci_dev = pci_dev;

	rc = pqi_pci_init(ctrl_info);
	if (rc)
		goto error;

	rc = pqi_ctrl_init(ctrl_info);
	if (rc)
		goto error;

	return 0;

error:
	pqi_remove_ctrl(ctrl_info);

	return rc;
}