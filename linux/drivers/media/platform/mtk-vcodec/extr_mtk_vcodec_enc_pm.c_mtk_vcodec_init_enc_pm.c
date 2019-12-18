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
struct mtk_vcodec_clk {int clk_num; struct mtk_vcodec_clk_info* clk_info; } ;
struct mtk_vcodec_pm {struct device* dev; struct device* larbvenclt; struct device* larbvenc; struct mtk_vcodec_clk venc_clk; struct mtk_vcodec_dev* mtkdev; } ;
struct mtk_vcodec_dev {struct platform_device* plat_dev; struct mtk_vcodec_pm pm; } ;
struct mtk_vcodec_clk_info {int /*<<< orphan*/  vcodec_clk; int /*<<< orphan*/  clk_name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ ) ; 
 struct mtk_vcodec_clk_info* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mtk_vcodec_pm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_v4l2_err (char*,...) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 int of_property_count_strings (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_string_index (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 

int mtk_vcodec_init_enc_pm(struct mtk_vcodec_dev *mtkdev)
{
	struct device_node *node;
	struct platform_device *pdev;
	struct mtk_vcodec_pm *pm;
	struct mtk_vcodec_clk *enc_clk;
	struct mtk_vcodec_clk_info *clk_info;
	int ret = 0, i = 0;
	struct device *dev;

	pdev = mtkdev->plat_dev;
	pm = &mtkdev->pm;
	memset(pm, 0, sizeof(struct mtk_vcodec_pm));
	pm->mtkdev = mtkdev;
	pm->dev = &pdev->dev;
	dev = &pdev->dev;
	enc_clk = &pm->venc_clk;

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

	enc_clk->clk_num = of_property_count_strings(pdev->dev.of_node,
		"clock-names");
	if (enc_clk->clk_num > 0) {
		enc_clk->clk_info = devm_kcalloc(&pdev->dev,
			enc_clk->clk_num, sizeof(*clk_info),
			GFP_KERNEL);
		if (!enc_clk->clk_info)
			return -ENOMEM;
	} else {
		mtk_v4l2_err("Failed to get venc clock count");
		return -EINVAL;
	}

	for (i = 0; i < enc_clk->clk_num; i++) {
		clk_info = &enc_clk->clk_info[i];
		ret = of_property_read_string_index(pdev->dev.of_node,
			"clock-names", i, &clk_info->clk_name);
		if (ret) {
			mtk_v4l2_err("venc failed to get clk name %d", i);
			return ret;
		}
		clk_info->vcodec_clk = devm_clk_get(&pdev->dev,
			clk_info->clk_name);
		if (IS_ERR(clk_info->vcodec_clk)) {
			mtk_v4l2_err("venc devm_clk_get (%d)%s fail", i,
				clk_info->clk_name);
			return PTR_ERR(clk_info->vcodec_clk);
		}
	}

	return ret;
}