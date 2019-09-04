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
typedef  int /*<<< orphan*/  u64 ;
struct pci_dev {int /*<<< orphan*/  dev; struct pci_bus* bus; } ;
struct pci_bus {struct pci_dev* self; struct pci_bus* parent; } ;
struct iommu_group {int dummy; } ;
struct group_for_pci_data {struct pci_dev* pdev; struct iommu_group* group; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct iommu_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQ_ACS_FLAGS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 struct iommu_group* get_pci_alias_group (struct pci_dev*,unsigned long*) ; 
 int /*<<< orphan*/  get_pci_alias_or_group ; 
 struct iommu_group* get_pci_function_alias_group (struct pci_dev*,unsigned long*) ; 
 struct iommu_group* iommu_group_alloc () ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_acs_path_enabled (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_for_each_dma_alias (struct pci_dev*,int /*<<< orphan*/ ,struct group_for_pci_data*) ; 
 int /*<<< orphan*/  pci_is_root_bus (struct pci_bus*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

struct iommu_group *pci_device_group(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct group_for_pci_data data;
	struct pci_bus *bus;
	struct iommu_group *group = NULL;
	u64 devfns[4] = { 0 };

	if (WARN_ON(!dev_is_pci(dev)))
		return ERR_PTR(-EINVAL);

	/*
	 * Find the upstream DMA alias for the device.  A device must not
	 * be aliased due to topology in order to have its own IOMMU group.
	 * If we find an alias along the way that already belongs to a
	 * group, use it.
	 */
	if (pci_for_each_dma_alias(pdev, get_pci_alias_or_group, &data))
		return data.group;

	pdev = data.pdev;

	/*
	 * Continue upstream from the point of minimum IOMMU granularity
	 * due to aliases to the point where devices are protected from
	 * peer-to-peer DMA by PCI ACS.  Again, if we find an existing
	 * group, use it.
	 */
	for (bus = pdev->bus; !pci_is_root_bus(bus); bus = bus->parent) {
		if (!bus->self)
			continue;

		if (pci_acs_path_enabled(bus->self, NULL, REQ_ACS_FLAGS))
			break;

		pdev = bus->self;

		group = iommu_group_get(&pdev->dev);
		if (group)
			return group;
	}

	/*
	 * Look for existing groups on device aliases.  If we alias another
	 * device or another device aliases us, use the same group.
	 */
	group = get_pci_alias_group(pdev, (unsigned long *)devfns);
	if (group)
		return group;

	/*
	 * Look for existing groups on non-isolated functions on the same
	 * slot and aliases of those funcions, if any.  No need to clear
	 * the search bitmap, the tested devfns are still valid.
	 */
	group = get_pci_function_alias_group(pdev, (unsigned long *)devfns);
	if (group)
		return group;

	/* No shared group found, allocate new */
	return iommu_group_alloc();
}