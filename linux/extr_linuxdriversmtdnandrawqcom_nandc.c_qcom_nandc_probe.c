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
struct resource {int /*<<< orphan*/  start; } ;
struct qcom_nand_controller {void* core_clk; void* aon_clk; int /*<<< orphan*/  base_dma; int /*<<< orphan*/  base_phys; void* base; void const* props; struct device* dev; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_nand_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_resource (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_resource (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_nand_controller*) ; 
 int qcom_nandc_alloc (struct qcom_nand_controller*) ; 
 int qcom_nandc_parse_dt (struct platform_device*) ; 
 int qcom_nandc_setup (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  qcom_nandc_unalloc (struct qcom_nand_controller*) ; 
 int qcom_probe_nand_devices (struct qcom_nand_controller*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int qcom_nandc_probe(struct platform_device *pdev)
{
	struct qcom_nand_controller *nandc;
	const void *dev_data;
	struct device *dev = &pdev->dev;
	struct resource *res;
	int ret;

	nandc = devm_kzalloc(&pdev->dev, sizeof(*nandc), GFP_KERNEL);
	if (!nandc)
		return -ENOMEM;

	platform_set_drvdata(pdev, nandc);
	nandc->dev = dev;

	dev_data = of_device_get_match_data(dev);
	if (!dev_data) {
		dev_err(&pdev->dev, "failed to get device data\n");
		return -ENODEV;
	}

	nandc->props = dev_data;

	nandc->core_clk = devm_clk_get(dev, "core");
	if (IS_ERR(nandc->core_clk))
		return PTR_ERR(nandc->core_clk);

	nandc->aon_clk = devm_clk_get(dev, "aon");
	if (IS_ERR(nandc->aon_clk))
		return PTR_ERR(nandc->aon_clk);

	ret = qcom_nandc_parse_dt(pdev);
	if (ret)
		return ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	nandc->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(nandc->base))
		return PTR_ERR(nandc->base);

	nandc->base_phys = res->start;
	nandc->base_dma = dma_map_resource(dev, res->start,
					   resource_size(res),
					   DMA_BIDIRECTIONAL, 0);
	if (!nandc->base_dma)
		return -ENXIO;

	ret = qcom_nandc_alloc(nandc);
	if (ret)
		goto err_nandc_alloc;

	ret = clk_prepare_enable(nandc->core_clk);
	if (ret)
		goto err_core_clk;

	ret = clk_prepare_enable(nandc->aon_clk);
	if (ret)
		goto err_aon_clk;

	ret = qcom_nandc_setup(nandc);
	if (ret)
		goto err_setup;

	ret = qcom_probe_nand_devices(nandc);
	if (ret)
		goto err_setup;

	return 0;

err_setup:
	clk_disable_unprepare(nandc->aon_clk);
err_aon_clk:
	clk_disable_unprepare(nandc->core_clk);
err_core_clk:
	qcom_nandc_unalloc(nandc);
err_nandc_alloc:
	dma_unmap_resource(dev, res->start, resource_size(res),
			   DMA_BIDIRECTIONAL, 0);

	return ret;
}