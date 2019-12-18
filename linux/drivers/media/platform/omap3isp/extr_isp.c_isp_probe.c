#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_18__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_7__ dev; } ;
struct TYPE_16__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_15__ {void* vdd; } ;
struct TYPE_14__ {void* vdd; } ;
struct isp_device {int revision; int irq_num; int /*<<< orphan*/  isp_mutex; TYPE_3__ notifier; int /*<<< orphan*/  v4l2_dev; TYPE_7__* dev; scalar_t__ mmio_hist_base_phys; scalar_t__* mmio_base; int /*<<< orphan*/ * clock; TYPE_2__ isp_csiphy2; TYPE_1__ isp_csiphy1; scalar_t__ ref_count; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  autoidle; int /*<<< orphan*/  syscon_offset; scalar_t__ syscon; int /*<<< orphan*/  phy_type; } ;
struct TYPE_17__ {int isp_rev; scalar_t__* offset; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 size_t ISP_CLK_CAM_ICK ; 
 int /*<<< orphan*/  ISP_REVISION ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int OMAP3_ISP_IOMEM_CSI2A_REGS1 ; 
 int OMAP3_ISP_IOMEM_CSIPHY2 ; 
 size_t OMAP3_ISP_IOMEM_HIST ; 
 int OMAP3_ISP_IOMEM_LAST ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_MAIN ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/ * __omap3isp_get (struct isp_device*,int) ; 
 int /*<<< orphan*/  __omap3isp_put (struct isp_device*,int) ; 
 int /*<<< orphan*/  autoidle ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*,int,int) ; 
 scalar_t__ devm_ioremap_resource (TYPE_7__*,struct resource*) ; 
 void* devm_regulator_get (TYPE_7__*,char*) ; 
 scalar_t__ devm_request_irq (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct isp_device*) ; 
 int dma_coerce_mask_and_coherent (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int fwnode_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int isp_attach_iommu (struct isp_device*) ; 
 int /*<<< orphan*/  isp_cleanup_modules (struct isp_device*) ; 
 int /*<<< orphan*/  isp_core_init (struct isp_device*,int) ; 
 int isp_create_links (struct isp_device*) ; 
 int /*<<< orphan*/  isp_detach_iommu (struct isp_device*) ; 
 int isp_get_clocks (struct isp_device*) ; 
 int isp_initialize_modules (struct isp_device*) ; 
 int /*<<< orphan*/  isp_isr ; 
 int isp_parse_of_endpoints (struct isp_device*) ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int isp_register_entities (struct isp_device*) ; 
 TYPE_6__* isp_res_maps ; 
 int isp_reset (struct isp_device*) ; 
 int /*<<< orphan*/  isp_subdev_notifier_ops ; 
 int /*<<< orphan*/  isp_unregister_entities (struct isp_device*) ; 
 int /*<<< orphan*/  isp_xclk_cleanup (struct isp_device*) ; 
 int isp_xclk_init (struct isp_device*) ; 
 int /*<<< orphan*/  kfree (struct isp_device*) ; 
 struct isp_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap3isp_put (struct isp_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct isp_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_3__*) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int isp_probe(struct platform_device *pdev)
{
	struct isp_device *isp;
	struct resource *mem;
	int ret;
	int i, m;

	isp = kzalloc(sizeof(*isp), GFP_KERNEL);
	if (!isp) {
		dev_err(&pdev->dev, "could not allocate memory\n");
		return -ENOMEM;
	}

	ret = fwnode_property_read_u32(of_fwnode_handle(pdev->dev.of_node),
				       "ti,phy-type", &isp->phy_type);
	if (ret)
		goto error_release_isp;

	isp->syscon = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						      "syscon");
	if (IS_ERR(isp->syscon)) {
		ret = PTR_ERR(isp->syscon);
		goto error_release_isp;
	}

	ret = of_property_read_u32_index(pdev->dev.of_node,
					 "syscon", 1, &isp->syscon_offset);
	if (ret)
		goto error_release_isp;

	isp->autoidle = autoidle;

	mutex_init(&isp->isp_mutex);
	spin_lock_init(&isp->stat_lock);
	v4l2_async_notifier_init(&isp->notifier);
	isp->dev = &pdev->dev;

	ret = isp_parse_of_endpoints(isp);
	if (ret < 0)
		goto error;

	isp->ref_count = 0;

	ret = dma_coerce_mask_and_coherent(isp->dev, DMA_BIT_MASK(32));
	if (ret)
		goto error;

	platform_set_drvdata(pdev, isp);

	/* Regulators */
	isp->isp_csiphy1.vdd = devm_regulator_get(&pdev->dev, "vdd-csiphy1");
	isp->isp_csiphy2.vdd = devm_regulator_get(&pdev->dev, "vdd-csiphy2");

	/* Clocks
	 *
	 * The ISP clock tree is revision-dependent. We thus need to enable ICLK
	 * manually to read the revision before calling __omap3isp_get().
	 *
	 * Start by mapping the ISP MMIO area, which is in two pieces.
	 * The ISP IOMMU is in between. Map both now, and fill in the
	 * ISP revision specific portions a little later in the
	 * function.
	 */
	for (i = 0; i < 2; i++) {
		unsigned int map_idx = i ? OMAP3_ISP_IOMEM_CSI2A_REGS1 : 0;

		mem = platform_get_resource(pdev, IORESOURCE_MEM, i);
		isp->mmio_base[map_idx] =
			devm_ioremap_resource(isp->dev, mem);
		if (IS_ERR(isp->mmio_base[map_idx]))
			return PTR_ERR(isp->mmio_base[map_idx]);
	}

	ret = isp_get_clocks(isp);
	if (ret < 0)
		goto error;

	ret = clk_enable(isp->clock[ISP_CLK_CAM_ICK]);
	if (ret < 0)
		goto error;

	isp->revision = isp_reg_readl(isp, OMAP3_ISP_IOMEM_MAIN, ISP_REVISION);
	dev_info(isp->dev, "Revision %d.%d found\n",
		 (isp->revision & 0xf0) >> 4, isp->revision & 0x0f);

	clk_disable(isp->clock[ISP_CLK_CAM_ICK]);

	if (__omap3isp_get(isp, false) == NULL) {
		ret = -ENODEV;
		goto error;
	}

	ret = isp_reset(isp);
	if (ret < 0)
		goto error_isp;

	ret = isp_xclk_init(isp);
	if (ret < 0)
		goto error_isp;

	/* Memory resources */
	for (m = 0; m < ARRAY_SIZE(isp_res_maps); m++)
		if (isp->revision == isp_res_maps[m].isp_rev)
			break;

	if (m == ARRAY_SIZE(isp_res_maps)) {
		dev_err(isp->dev, "No resource map found for ISP rev %d.%d\n",
			(isp->revision & 0xf0) >> 4, isp->revision & 0xf);
		ret = -ENODEV;
		goto error_isp;
	}

	for (i = 1; i < OMAP3_ISP_IOMEM_CSI2A_REGS1; i++)
		isp->mmio_base[i] =
			isp->mmio_base[0] + isp_res_maps[m].offset[i];

	for (i = OMAP3_ISP_IOMEM_CSIPHY2; i < OMAP3_ISP_IOMEM_LAST; i++)
		isp->mmio_base[i] =
			isp->mmio_base[OMAP3_ISP_IOMEM_CSI2A_REGS1]
			+ isp_res_maps[m].offset[i];

	isp->mmio_hist_base_phys =
		mem->start + isp_res_maps[m].offset[OMAP3_ISP_IOMEM_HIST];

	/* IOMMU */
	ret = isp_attach_iommu(isp);
	if (ret < 0) {
		dev_err(&pdev->dev, "unable to attach to IOMMU\n");
		goto error_isp;
	}

	/* Interrupt */
	ret = platform_get_irq(pdev, 0);
	if (ret <= 0) {
		ret = -ENODEV;
		goto error_iommu;
	}
	isp->irq_num = ret;

	if (devm_request_irq(isp->dev, isp->irq_num, isp_isr, IRQF_SHARED,
			     "OMAP3 ISP", isp)) {
		dev_err(isp->dev, "Unable to request IRQ\n");
		ret = -EINVAL;
		goto error_iommu;
	}

	/* Entities */
	ret = isp_initialize_modules(isp);
	if (ret < 0)
		goto error_iommu;

	ret = isp_register_entities(isp);
	if (ret < 0)
		goto error_modules;

	ret = isp_create_links(isp);
	if (ret < 0)
		goto error_register_entities;

	isp->notifier.ops = &isp_subdev_notifier_ops;

	ret = v4l2_async_notifier_register(&isp->v4l2_dev, &isp->notifier);
	if (ret)
		goto error_register_entities;

	isp_core_init(isp, 1);
	omap3isp_put(isp);

	return 0;

error_register_entities:
	isp_unregister_entities(isp);
error_modules:
	isp_cleanup_modules(isp);
error_iommu:
	isp_detach_iommu(isp);
error_isp:
	isp_xclk_cleanup(isp);
	__omap3isp_put(isp, false);
error:
	v4l2_async_notifier_cleanup(&isp->notifier);
	mutex_destroy(&isp->isp_mutex);
error_release_isp:
	kfree(isp);

	return ret;
}