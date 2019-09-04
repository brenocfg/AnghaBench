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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct mtk_vcodec_pm {void* venc_lt_sel; void* univpll1_d2; void* venc_sel; void* vencpll_d2; struct device* dev; struct device* larbvenclt; struct device* larbvenc; struct mtk_vcodec_dev* mtkdev; } ;
struct mtk_vcodec_dev {struct platform_device* plat_dev; struct mtk_vcodec_pm pm; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  memset (struct mtk_vcodec_pm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 

int mtk_vcodec_init_enc_pm(struct mtk_vcodec_dev *mtkdev)
{
	struct device_node *node;
	struct platform_device *pdev;
	struct device *dev;
	struct mtk_vcodec_pm *pm;
	int ret = 0;

	pdev = mtkdev->plat_dev;
	pm = &mtkdev->pm;
	memset(pm, 0, sizeof(struct mtk_vcodec_pm));
	pm->mtkdev = mtkdev;
	pm->dev = &pdev->dev;
	dev = &pdev->dev;

	node = of_parse_phandle(dev->of_node, "mediatek,larb", 0);
	if (!node) {
		mtk_v4l2_err("no mediatek,larb found");
		return -ENODEV;
	}
	pdev = of_find_device_by_node(node);
	of_node_put(node);
	if (!pdev) {
		mtk_v4l2_err("no mediatek,larb device found");
		return -ENODEV;
	}
	pm->larbvenc = &pdev->dev;

	node = of_parse_phandle(dev->of_node, "mediatek,larb", 1);
	if (!node) {
		mtk_v4l2_err("no mediatek,larb found");
		return -ENODEV;
	}

	pdev = of_find_device_by_node(node);
	of_node_put(node);
	if (!pdev) {
		mtk_v4l2_err("no mediatek,larb device found");
		return -ENODEV;
	}

	pm->larbvenclt = &pdev->dev;
	pdev = mtkdev->plat_dev;
	pm->dev = &pdev->dev;

	pm->vencpll_d2 = devm_clk_get(&pdev->dev, "venc_sel_src");
	if (IS_ERR(pm->vencpll_d2)) {
		mtk_v4l2_err("devm_clk_get vencpll_d2 fail");
		ret = PTR_ERR(pm->vencpll_d2);
	}

	pm->venc_sel = devm_clk_get(&pdev->dev, "venc_sel");
	if (IS_ERR(pm->venc_sel)) {
		mtk_v4l2_err("devm_clk_get venc_sel fail");
		ret = PTR_ERR(pm->venc_sel);
	}

	pm->univpll1_d2 = devm_clk_get(&pdev->dev, "venc_lt_sel_src");
	if (IS_ERR(pm->univpll1_d2)) {
		mtk_v4l2_err("devm_clk_get univpll1_d2 fail");
		ret = PTR_ERR(pm->univpll1_d2);
	}

	pm->venc_lt_sel = devm_clk_get(&pdev->dev, "venc_lt_sel");
	if (IS_ERR(pm->venc_lt_sel)) {
		mtk_v4l2_err("devm_clk_get venc_lt_sel fail");
		ret = PTR_ERR(pm->venc_lt_sel);
	}

	return ret;
}