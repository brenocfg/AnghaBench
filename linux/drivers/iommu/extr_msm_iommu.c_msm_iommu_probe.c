#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_9__ {TYPE_1__* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct msm_iommu_dev {scalar_t__ irq; int ncb; void* pclk; void* clk; void* base; int /*<<< orphan*/  iommu; TYPE_2__* dev; int /*<<< orphan*/  dev_node; int /*<<< orphan*/  ctx_list; } ;
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_8__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENODEV ; 
 int GET_PAR (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SET_M (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_PAR (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_V2PCFG (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_V2PPR (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_set_iommu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int clk_prepare (void*) ; 
 int /*<<< orphan*/  clk_unprepare (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct msm_iommu_dev* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct msm_iommu_dev*) ; 
 int iommu_device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_fwnode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_device_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iommu_device_sysfs_add (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_iommu_fault_handler ; 
 int /*<<< orphan*/  msm_iommu_ops ; 
 int /*<<< orphan*/  msm_iommu_reset (void*,int) ; 
 int of_property_read_u32 (TYPE_1__*,char*,int*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,void*,scalar_t__,int) ; 
 int /*<<< orphan*/  qcom_iommu_devices ; 

__attribute__((used)) static int msm_iommu_probe(struct platform_device *pdev)
{
	struct resource *r;
	resource_size_t ioaddr;
	struct msm_iommu_dev *iommu;
	int ret, par, val;

	iommu = devm_kzalloc(&pdev->dev, sizeof(*iommu), GFP_KERNEL);
	if (!iommu)
		return -ENODEV;

	iommu->dev = &pdev->dev;
	INIT_LIST_HEAD(&iommu->ctx_list);

	iommu->pclk = devm_clk_get(iommu->dev, "smmu_pclk");
	if (IS_ERR(iommu->pclk)) {
		dev_err(iommu->dev, "could not get smmu_pclk\n");
		return PTR_ERR(iommu->pclk);
	}

	ret = clk_prepare(iommu->pclk);
	if (ret) {
		dev_err(iommu->dev, "could not prepare smmu_pclk\n");
		return ret;
	}

	iommu->clk = devm_clk_get(iommu->dev, "iommu_clk");
	if (IS_ERR(iommu->clk)) {
		dev_err(iommu->dev, "could not get iommu_clk\n");
		clk_unprepare(iommu->pclk);
		return PTR_ERR(iommu->clk);
	}

	ret = clk_prepare(iommu->clk);
	if (ret) {
		dev_err(iommu->dev, "could not prepare iommu_clk\n");
		clk_unprepare(iommu->pclk);
		return ret;
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	iommu->base = devm_ioremap_resource(iommu->dev, r);
	if (IS_ERR(iommu->base)) {
		dev_err(iommu->dev, "could not get iommu base\n");
		ret = PTR_ERR(iommu->base);
		goto fail;
	}
	ioaddr = r->start;

	iommu->irq = platform_get_irq(pdev, 0);
	if (iommu->irq < 0) {
		ret = -ENODEV;
		goto fail;
	}

	ret = of_property_read_u32(iommu->dev->of_node, "qcom,ncb", &val);
	if (ret) {
		dev_err(iommu->dev, "could not get ncb\n");
		goto fail;
	}
	iommu->ncb = val;

	msm_iommu_reset(iommu->base, iommu->ncb);
	SET_M(iommu->base, 0, 1);
	SET_PAR(iommu->base, 0, 0);
	SET_V2PCFG(iommu->base, 0, 1);
	SET_V2PPR(iommu->base, 0, 0);
	par = GET_PAR(iommu->base, 0);
	SET_V2PCFG(iommu->base, 0, 0);
	SET_M(iommu->base, 0, 0);

	if (!par) {
		pr_err("Invalid PAR value detected\n");
		ret = -ENODEV;
		goto fail;
	}

	ret = devm_request_threaded_irq(iommu->dev, iommu->irq, NULL,
					msm_iommu_fault_handler,
					IRQF_ONESHOT | IRQF_SHARED,
					"msm_iommu_secure_irpt_handler",
					iommu);
	if (ret) {
		pr_err("Request IRQ %d failed with ret=%d\n", iommu->irq, ret);
		goto fail;
	}

	list_add(&iommu->dev_node, &qcom_iommu_devices);

	ret = iommu_device_sysfs_add(&iommu->iommu, iommu->dev, NULL,
				     "msm-smmu.%pa", &ioaddr);
	if (ret) {
		pr_err("Could not add msm-smmu at %pa to sysfs\n", &ioaddr);
		goto fail;
	}

	iommu_device_set_ops(&iommu->iommu, &msm_iommu_ops);
	iommu_device_set_fwnode(&iommu->iommu, &pdev->dev.of_node->fwnode);

	ret = iommu_device_register(&iommu->iommu);
	if (ret) {
		pr_err("Could not register msm-smmu at %pa\n", &ioaddr);
		goto fail;
	}

	bus_set_iommu(&platform_bus_type, &msm_iommu_ops);

	pr_info("device mapped at %p, irq %d with %d ctx banks\n",
		iommu->base, iommu->irq, iommu->ncb);

	return ret;
fail:
	clk_unprepare(iommu->clk);
	clk_unprepare(iommu->pclk);
	return ret;
}