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
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mtk_vcodec_pm {void* vdec_bus_clk_src; void* venc_lt_sel; void* vencpll; void* vdecpll; void* vdec_sel; void* clk_cci400_sel; void* univpll_d2; void* vcodecpll; TYPE_1__* dev; TYPE_1__* larbvdec; struct mtk_vcodec_dev* mtkdev; } ;
struct mtk_vcodec_dev {struct platform_device* plat_dev; struct mtk_vcodec_pm pm; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ WARN_ON (int) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 

int mtk_vcodec_init_dec_pm(struct mtk_vcodec_dev *mtkdev)
{
	struct device_node *node;
	struct platform_device *pdev;
	struct mtk_vcodec_pm *pm;
	int ret = 0;

	pdev = mtkdev->plat_dev;
	pm = &mtkdev->pm;
	pm->mtkdev = mtkdev;
	node = of_parse_phandle(pdev->dev.of_node, "mediatek,larb", 0);
	if (!node) {
		mtk_v4l2_err("of_parse_phandle mediatek,larb fail!");
		return -1;
	}

	pdev = of_find_device_by_node(node);
	if (WARN_ON(!pdev)) {
		of_node_put(node);
		return -1;
	}
	pm->larbvdec = &pdev->dev;
	pdev = mtkdev->plat_dev;
	pm->dev = &pdev->dev;

	pm->vcodecpll = devm_clk_get(&pdev->dev, "vcodecpll");
	if (IS_ERR(pm->vcodecpll)) {
		mtk_v4l2_err("devm_clk_get vcodecpll fail");
		ret = PTR_ERR(pm->vcodecpll);
	}

	pm->univpll_d2 = devm_clk_get(&pdev->dev, "univpll_d2");
	if (IS_ERR(pm->univpll_d2)) {
		mtk_v4l2_err("devm_clk_get univpll_d2 fail");
		ret = PTR_ERR(pm->univpll_d2);
	}

	pm->clk_cci400_sel = devm_clk_get(&pdev->dev, "clk_cci400_sel");
	if (IS_ERR(pm->clk_cci400_sel)) {
		mtk_v4l2_err("devm_clk_get clk_cci400_sel fail");
		ret = PTR_ERR(pm->clk_cci400_sel);
	}

	pm->vdec_sel = devm_clk_get(&pdev->dev, "vdec_sel");
	if (IS_ERR(pm->vdec_sel)) {
		mtk_v4l2_err("devm_clk_get vdec_sel fail");
		ret = PTR_ERR(pm->vdec_sel);
	}

	pm->vdecpll = devm_clk_get(&pdev->dev, "vdecpll");
	if (IS_ERR(pm->vdecpll)) {
		mtk_v4l2_err("devm_clk_get vdecpll fail");
		ret = PTR_ERR(pm->vdecpll);
	}

	pm->vencpll = devm_clk_get(&pdev->dev, "vencpll");
	if (IS_ERR(pm->vencpll)) {
		mtk_v4l2_err("devm_clk_get vencpll fail");
		ret = PTR_ERR(pm->vencpll);
	}

	pm->venc_lt_sel = devm_clk_get(&pdev->dev, "venc_lt_sel");
	if (IS_ERR(pm->venc_lt_sel)) {
		mtk_v4l2_err("devm_clk_get venc_lt_sel fail");
		ret = PTR_ERR(pm->venc_lt_sel);
	}

	pm->vdec_bus_clk_src = devm_clk_get(&pdev->dev, "vdec_bus_clk_src");
	if (IS_ERR(pm->vdec_bus_clk_src)) {
		mtk_v4l2_err("devm_clk_get vdec_bus_clk_src");
		ret = PTR_ERR(pm->vdec_bus_clk_src);
	}

	pm_runtime_enable(&pdev->dev);

	return ret;
}