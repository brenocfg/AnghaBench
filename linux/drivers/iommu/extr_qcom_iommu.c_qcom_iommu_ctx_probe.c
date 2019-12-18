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
struct resource {int dummy; } ;
struct qcom_iommu_dev {struct qcom_iommu_ctx** ctxs; } ;
struct qcom_iommu_ctx {int asid; int /*<<< orphan*/  base; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SMMU_CB_FSR ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct qcom_iommu_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_iommu_ctx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct qcom_iommu_ctx*) ; 
 int get_asid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_readl (struct qcom_iommu_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_writel (struct qcom_iommu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_iommu_ctx*) ; 
 int /*<<< orphan*/  qcom_iommu_fault ; 

__attribute__((used)) static int qcom_iommu_ctx_probe(struct platform_device *pdev)
{
	struct qcom_iommu_ctx *ctx;
	struct device *dev = &pdev->dev;
	struct qcom_iommu_dev *qcom_iommu = dev_get_drvdata(dev->parent);
	struct resource *res;
	int ret, irq;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = dev;
	platform_set_drvdata(pdev, ctx);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(ctx->base))
		return PTR_ERR(ctx->base);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return -ENODEV;

	/* clear IRQs before registering fault handler, just in case the
	 * boot-loader left us a surprise:
	 */
	iommu_writel(ctx, ARM_SMMU_CB_FSR, iommu_readl(ctx, ARM_SMMU_CB_FSR));

	ret = devm_request_irq(dev, irq,
			       qcom_iommu_fault,
			       IRQF_SHARED,
			       "qcom-iommu-fault",
			       ctx);
	if (ret) {
		dev_err(dev, "failed to request IRQ %u\n", irq);
		return ret;
	}

	ret = get_asid(dev->of_node);
	if (ret < 0) {
		dev_err(dev, "missing reg property\n");
		return ret;
	}

	ctx->asid = ret;

	dev_dbg(dev, "found asid %u\n", ctx->asid);

	qcom_iommu->ctxs[ctx->asid - 1] = ctx;

	return 0;
}