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
struct tegra_smmu_soc {int num_tlb_lines; scalar_t__ supports_round_robin_arbitration; scalar_t__ supports_request_limit; int /*<<< orphan*/  num_asids; } ;
struct tegra_smmu {int pfn_mask; int tlb_mask; int /*<<< orphan*/  iommu; struct tegra_smmu_soc const* soc; struct tegra_mc* mc; struct device* dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  groups; void* asids; } ;
struct tegra_mc {TYPE_1__* soc; int /*<<< orphan*/  regs; struct tegra_smmu* smmu; } ;
struct device {int /*<<< orphan*/  fwnode; } ;
struct TYPE_2__ {int num_address_bits; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int BIT_MASK (int) ; 
 int /*<<< orphan*/  CONFIG_DEBUG_FS ; 
 int ENOMEM ; 
 struct tegra_smmu* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SMMU_CONFIG ; 
 int SMMU_CONFIG_ENABLE ; 
 int /*<<< orphan*/  SMMU_PTC_CONFIG ; 
 int SMMU_PTC_CONFIG_ENABLE ; 
 int SMMU_PTC_CONFIG_INDEX_MAP (int) ; 
 int SMMU_PTC_CONFIG_REQ_LIMIT (int) ; 
 int /*<<< orphan*/  SMMU_TLB_CONFIG ; 
 int SMMU_TLB_CONFIG_ACTIVE_LINES (struct tegra_smmu*) ; 
 int SMMU_TLB_CONFIG_HIT_UNDER_MISS ; 
 int SMMU_TLB_CONFIG_ROUND_ROBIN_ARBITRATION ; 
 int bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_kzalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_device_sysfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  smmu_flush (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_flush_ptc_all (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_flush_tlb (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_smmu_ahb_enable () ; 
 int /*<<< orphan*/  tegra_smmu_debugfs_init (struct tegra_smmu*) ; 
 int /*<<< orphan*/  tegra_smmu_ops ; 

struct tegra_smmu *tegra_smmu_probe(struct device *dev,
				    const struct tegra_smmu_soc *soc,
				    struct tegra_mc *mc)
{
	struct tegra_smmu *smmu;
	size_t size;
	u32 value;
	int err;

	smmu = devm_kzalloc(dev, sizeof(*smmu), GFP_KERNEL);
	if (!smmu)
		return ERR_PTR(-ENOMEM);

	/*
	 * This is a bit of a hack. Ideally we'd want to simply return this
	 * value. However the IOMMU registration process will attempt to add
	 * all devices to the IOMMU when bus_set_iommu() is called. In order
	 * not to rely on global variables to track the IOMMU instance, we
	 * set it here so that it can be looked up from the .add_device()
	 * callback via the IOMMU device's .drvdata field.
	 */
	mc->smmu = smmu;

	size = BITS_TO_LONGS(soc->num_asids) * sizeof(long);

	smmu->asids = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!smmu->asids)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&smmu->groups);
	mutex_init(&smmu->lock);

	smmu->regs = mc->regs;
	smmu->soc = soc;
	smmu->dev = dev;
	smmu->mc = mc;

	smmu->pfn_mask = BIT_MASK(mc->soc->num_address_bits - PAGE_SHIFT) - 1;
	dev_dbg(dev, "address bits: %u, PFN mask: %#lx\n",
		mc->soc->num_address_bits, smmu->pfn_mask);
	smmu->tlb_mask = (smmu->soc->num_tlb_lines << 1) - 1;
	dev_dbg(dev, "TLB lines: %u, mask: %#lx\n", smmu->soc->num_tlb_lines,
		smmu->tlb_mask);

	value = SMMU_PTC_CONFIG_ENABLE | SMMU_PTC_CONFIG_INDEX_MAP(0x3f);

	if (soc->supports_request_limit)
		value |= SMMU_PTC_CONFIG_REQ_LIMIT(8);

	smmu_writel(smmu, value, SMMU_PTC_CONFIG);

	value = SMMU_TLB_CONFIG_HIT_UNDER_MISS |
		SMMU_TLB_CONFIG_ACTIVE_LINES(smmu);

	if (soc->supports_round_robin_arbitration)
		value |= SMMU_TLB_CONFIG_ROUND_ROBIN_ARBITRATION;

	smmu_writel(smmu, value, SMMU_TLB_CONFIG);

	smmu_flush_ptc_all(smmu);
	smmu_flush_tlb(smmu);
	smmu_writel(smmu, SMMU_CONFIG_ENABLE, SMMU_CONFIG);
	smmu_flush(smmu);

	tegra_smmu_ahb_enable();

	err = iommu_device_sysfs_add(&smmu->iommu, dev, NULL, dev_name(dev));
	if (err)
		return ERR_PTR(err);

	iommu_device_set_ops(&smmu->iommu, &tegra_smmu_ops);
	iommu_device_set_fwnode(&smmu->iommu, dev->fwnode);

	err = iommu_device_register(&smmu->iommu);
	if (err) {
		iommu_device_sysfs_remove(&smmu->iommu);
		return ERR_PTR(err);
	}

	err = bus_set_iommu(&platform_bus_type, &tegra_smmu_ops);
	if (err < 0) {
		iommu_device_unregister(&smmu->iommu);
		iommu_device_sysfs_remove(&smmu->iommu);
		return ERR_PTR(err);
	}

	if (IS_ENABLED(CONFIG_DEBUG_FS))
		tegra_smmu_debugfs_init(smmu);

	return smmu;
}