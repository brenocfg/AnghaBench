#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_14__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct ipmmu_vmsa_device {int /*<<< orphan*/  iommu; TYPE_2__* features; int /*<<< orphan*/  ctx; struct ipmmu_vmsa_device* root; int /*<<< orphan*/  num_ctx; int /*<<< orphan*/  base; int /*<<< orphan*/  utlb_ctx; int /*<<< orphan*/  lock; TYPE_3__* dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  has_cache_leaf_nodes; scalar_t__ reserved_context; int /*<<< orphan*/  number_of_contexts; scalar_t__ use_ns_alias_offset; int /*<<< orphan*/  num_utlbs; } ;
struct TYPE_12__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IM_NS_ALIAS_OFFSET ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IPMMU_CTX_INVALID ; 
 int /*<<< orphan*/  IPMMU_CTX_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct ipmmu_vmsa_device* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipmmu_vmsa_device*) ; 
 int /*<<< orphan*/  dma_set_mask_and_coherent (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_present (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipmmu_device_reset (struct ipmmu_vmsa_device*) ; 
 struct ipmmu_vmsa_device* ipmmu_find_root () ; 
 int /*<<< orphan*/  ipmmu_irq ; 
 scalar_t__ ipmmu_is_root (struct ipmmu_vmsa_device*) ; 
 int /*<<< orphan*/  ipmmu_ops ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* of_device_get_match_data (TYPE_3__*) ; 
 int /*<<< orphan*/  of_find_property (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ipmmu_vmsa_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipmmu_probe(struct platform_device *pdev)
{
	struct ipmmu_vmsa_device *mmu;
	struct resource *res;
	int irq;
	int ret;

	mmu = devm_kzalloc(&pdev->dev, sizeof(*mmu), GFP_KERNEL);
	if (!mmu) {
		dev_err(&pdev->dev, "cannot allocate device data\n");
		return -ENOMEM;
	}

	mmu->dev = &pdev->dev;
	spin_lock_init(&mmu->lock);
	bitmap_zero(mmu->ctx, IPMMU_CTX_MAX);
	mmu->features = of_device_get_match_data(&pdev->dev);
	memset(mmu->utlb_ctx, IPMMU_CTX_INVALID, mmu->features->num_utlbs);
	dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));

	/* Map I/O memory and request IRQ. */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mmu->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mmu->base))
		return PTR_ERR(mmu->base);

	/*
	 * The IPMMU has two register banks, for secure and non-secure modes.
	 * The bank mapped at the beginning of the IPMMU address space
	 * corresponds to the running mode of the CPU. When running in secure
	 * mode the non-secure register bank is also available at an offset.
	 *
	 * Secure mode operation isn't clearly documented and is thus currently
	 * not implemented in the driver. Furthermore, preliminary tests of
	 * non-secure operation with the main register bank were not successful.
	 * Offset the registers base unconditionally to point to the non-secure
	 * alias space for now.
	 */
	if (mmu->features->use_ns_alias_offset)
		mmu->base += IM_NS_ALIAS_OFFSET;

	mmu->num_ctx = min(IPMMU_CTX_MAX, mmu->features->number_of_contexts);

	/*
	 * Determine if this IPMMU instance is a root device by checking for
	 * the lack of has_cache_leaf_nodes flag or renesas,ipmmu-main property.
	 */
	if (!mmu->features->has_cache_leaf_nodes ||
	    !of_find_property(pdev->dev.of_node, "renesas,ipmmu-main", NULL))
		mmu->root = mmu;
	else
		mmu->root = ipmmu_find_root();

	/*
	 * Wait until the root device has been registered for sure.
	 */
	if (!mmu->root)
		return -EPROBE_DEFER;

	/* Root devices have mandatory IRQs */
	if (ipmmu_is_root(mmu)) {
		irq = platform_get_irq(pdev, 0);
		if (irq < 0)
			return irq;

		ret = devm_request_irq(&pdev->dev, irq, ipmmu_irq, 0,
				       dev_name(&pdev->dev), mmu);
		if (ret < 0) {
			dev_err(&pdev->dev, "failed to request IRQ %d\n", irq);
			return ret;
		}

		ipmmu_device_reset(mmu);

		if (mmu->features->reserved_context) {
			dev_info(&pdev->dev, "IPMMU context 0 is reserved\n");
			set_bit(0, mmu->ctx);
		}
	}

	/*
	 * Register the IPMMU to the IOMMU subsystem in the following cases:
	 * - R-Car Gen2 IPMMU (all devices registered)
	 * - R-Car Gen3 IPMMU (leaf devices only - skip root IPMMU-MM device)
	 */
	if (!mmu->features->has_cache_leaf_nodes || !ipmmu_is_root(mmu)) {
		ret = iommu_device_sysfs_add(&mmu->iommu, &pdev->dev, NULL,
					     dev_name(&pdev->dev));
		if (ret)
			return ret;

		iommu_device_set_ops(&mmu->iommu, &ipmmu_ops);
		iommu_device_set_fwnode(&mmu->iommu,
					&pdev->dev.of_node->fwnode);

		ret = iommu_device_register(&mmu->iommu);
		if (ret)
			return ret;

#if defined(CONFIG_IOMMU_DMA)
		if (!iommu_present(&platform_bus_type))
			bus_set_iommu(&platform_bus_type, &ipmmu_ops);
#endif
	}

	/*
	 * We can't create the ARM mapping here as it requires the bus to have
	 * an IOMMU, which only happens when bus_set_iommu() is called in
	 * ipmmu_init() after the probe function returns.
	 */

	platform_set_drvdata(pdev, mmu);

	return 0;
}