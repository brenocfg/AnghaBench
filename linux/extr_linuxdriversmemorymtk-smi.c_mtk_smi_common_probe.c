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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mtk_smi {void* clk_async; void* smi_ao_base; void* clk_smi; void* clk_apb; struct device* dev; } ;
typedef  enum mtk_smi_gen { ____Placeholder_mtk_smi_gen } mtk_smi_gen ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int MTK_SMI_GEN1 ; 
 int PTR_ERR (void*) ; 
 int clk_prepare_enable (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mtk_smi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_smi*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 

__attribute__((used)) static int mtk_smi_common_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_smi *common;
	struct resource *res;
	enum mtk_smi_gen smi_gen;
	int ret;

	common = devm_kzalloc(dev, sizeof(*common), GFP_KERNEL);
	if (!common)
		return -ENOMEM;
	common->dev = dev;

	common->clk_apb = devm_clk_get(dev, "apb");
	if (IS_ERR(common->clk_apb))
		return PTR_ERR(common->clk_apb);

	common->clk_smi = devm_clk_get(dev, "smi");
	if (IS_ERR(common->clk_smi))
		return PTR_ERR(common->clk_smi);

	/*
	 * for mtk smi gen 1, we need to get the ao(always on) base to config
	 * m4u port, and we need to enable the aync clock for transform the smi
	 * clock into emi clock domain, but for mtk smi gen2, there's no smi ao
	 * base.
	 */
	smi_gen = (enum mtk_smi_gen)of_device_get_match_data(dev);
	if (smi_gen == MTK_SMI_GEN1) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		common->smi_ao_base = devm_ioremap_resource(dev, res);
		if (IS_ERR(common->smi_ao_base))
			return PTR_ERR(common->smi_ao_base);

		common->clk_async = devm_clk_get(dev, "async");
		if (IS_ERR(common->clk_async))
			return PTR_ERR(common->clk_async);

		ret = clk_prepare_enable(common->clk_async);
		if (ret)
			return ret;
	}
	pm_runtime_enable(dev);
	platform_set_drvdata(pdev, common);
	return 0;
}