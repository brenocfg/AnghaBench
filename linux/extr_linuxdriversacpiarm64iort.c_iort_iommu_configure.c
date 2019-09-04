#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  iommu_fwspec; } ;
struct pci_bus {struct device dev; } ;
struct iort_pci_alias_info {struct acpi_iort_node* node; struct device* dev; } ;
struct iommu_ops {int dummy; } ;
struct acpi_iort_node {int dummy; } ;
struct TYPE_3__ {struct pci_bus* bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_IORT_NODE_NAMED_COMPONENT ; 
 int /*<<< orphan*/  ACPI_IORT_NODE_PCI_ROOT_COMPLEX ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct iommu_ops* ERR_PTR (int) ; 
 int /*<<< orphan*/  IORT_IOMMU_TYPE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int iort_add_device_replay (struct iommu_ops const*,struct device*) ; 
 struct iommu_ops* iort_fwspec_iommu_ops (int /*<<< orphan*/ ) ; 
 int iort_iommu_xlate (struct device*,struct acpi_iort_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iort_match_node_callback ; 
 struct acpi_iort_node* iort_node_map_platform_id (struct acpi_iort_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iort_pci_iommu_init ; 
 struct acpi_iort_node* iort_scan_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int pci_for_each_dma_alias (TYPE_1__*,int /*<<< orphan*/ ,struct iort_pci_alias_info*) ; 
 TYPE_1__* to_pci_dev (struct device*) ; 

const struct iommu_ops *iort_iommu_configure(struct device *dev)
{
	struct acpi_iort_node *node, *parent;
	const struct iommu_ops *ops;
	u32 streamid = 0;
	int err = -ENODEV;

	/*
	 * If we already translated the fwspec there
	 * is nothing left to do, return the iommu_ops.
	 */
	ops = iort_fwspec_iommu_ops(dev->iommu_fwspec);
	if (ops)
		return ops;

	if (dev_is_pci(dev)) {
		struct pci_bus *bus = to_pci_dev(dev)->bus;
		struct iort_pci_alias_info info = { .dev = dev };

		node = iort_scan_node(ACPI_IORT_NODE_PCI_ROOT_COMPLEX,
				      iort_match_node_callback, &bus->dev);
		if (!node)
			return NULL;

		info.node = node;
		err = pci_for_each_dma_alias(to_pci_dev(dev),
					     iort_pci_iommu_init, &info);
	} else {
		int i = 0;

		node = iort_scan_node(ACPI_IORT_NODE_NAMED_COMPONENT,
				      iort_match_node_callback, dev);
		if (!node)
			return NULL;

		do {
			parent = iort_node_map_platform_id(node, &streamid,
							   IORT_IOMMU_TYPE,
							   i++);

			if (parent)
				err = iort_iommu_xlate(dev, parent, streamid);
		} while (parent && !err);
	}

	/*
	 * If we have reason to believe the IOMMU driver missed the initial
	 * add_device callback for dev, replay it to get things in order.
	 */
	if (!err) {
		ops = iort_fwspec_iommu_ops(dev->iommu_fwspec);
		err = iort_add_device_replay(ops, dev);
	}

	/* Ignore all other errors apart from EPROBE_DEFER */
	if (err == -EPROBE_DEFER) {
		ops = ERR_PTR(err);
	} else if (err) {
		dev_dbg(dev, "Adding to IOMMU failed: %d\n", err);
		ops = NULL;
	}

	return ops;
}