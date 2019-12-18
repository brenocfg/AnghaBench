#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct of_phandle_iterator {int cur_count; int /*<<< orphan*/ * cur; struct device_node* node; } ;
struct device_node {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct arm_smmu_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __arm_smmu_get_pci_sid ; 
 int /*<<< orphan*/  __find_legacy_master_phandle ; 
 TYPE_2__ arm_smmu_driver ; 
 int /*<<< orphan*/  arm_smmu_ops ; 
 struct device_node* dev_get_dev_node (struct device*) ; 
 struct arm_smmu_device* dev_get_drvdata (struct device*) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 int driver_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int iommu_fwspec_add_ids (struct device*,int /*<<< orphan*/ *,int) ; 
 int iommu_fwspec_init (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_phandle_iterator_args (struct of_phandle_iterator*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_for_each_dma_alias (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 

__attribute__((used)) static int arm_smmu_register_legacy_master(struct device *dev,
					   struct arm_smmu_device **smmu)
{
	struct device *smmu_dev;
	struct device_node *np;
	struct of_phandle_iterator it;
	void *data = &it;
	u32 *sids;
	__be32 pci_sid;
	int err;

	np = dev_get_dev_node(dev);
	if (!np || !of_find_property(np, "#stream-id-cells", NULL)) {
		of_node_put(np);
		return -ENODEV;
	}

	it.node = np;
	err = driver_for_each_device(&arm_smmu_driver.driver, NULL, &data,
				     __find_legacy_master_phandle);
	smmu_dev = data;
	of_node_put(np);
	if (err == 0)
		return -ENODEV;
	if (err < 0)
		return err;

	if (dev_is_pci(dev)) {
		/* "mmu-masters" assumes Stream ID == Requester ID */
		pci_for_each_dma_alias(to_pci_dev(dev), __arm_smmu_get_pci_sid,
				       &pci_sid);
		it.cur = &pci_sid;
		it.cur_count = 1;
	}

	err = iommu_fwspec_init(dev, &smmu_dev->of_node->fwnode,
				&arm_smmu_ops);
	if (err)
		return err;

	sids = kcalloc(it.cur_count, sizeof(*sids), GFP_KERNEL);
	if (!sids)
		return -ENOMEM;

	*smmu = dev_get_drvdata(smmu_dev);
	of_phandle_iterator_args(&it, sids, it.cur_count);
	err = iommu_fwspec_add_ids(dev, sids, it.cur_count);
	kfree(sids);
	return err;
}